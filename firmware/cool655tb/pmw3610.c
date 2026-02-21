/* Copyright 2021 Gompa (@Gompa)
 * Modifications Copyright 2025 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// https://github.com/shinoaliceKabocha/choco60_track/tree/master/keymaps/default

#include "pointing_device.h"

#include "debug.h"
#include "gpio.h"
#include "pmw3610.h"
#include "pointing_device_internal.h"
#include "wait.h"

#define REG_PID1 0x00
#define REG_PID2 0x01
#define REG_STAT 0x02
#define REG_X 0x03
#define REG_Y 0x04
#define REG_CONFIGURATION 0x06
#define REG_CPI_X 0x0D
#define REG_CPI_Y 0x0E

#define REG_PROTECT 0x09

#define VAL_PROTECT_DISABLE 0x5A
#define VAL_PROTECT_ENABLE 0x00

#define constrain(amt, low, high)                                              \
  ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

// CPI values
enum cpi_values {
  CPI400,  // 0b000
  CPI500,  // 0b001
  CPI600,  // 0b010
  CPI800,  // 0b011
  CPI1000, // 0b100
  CPI1200, // 0b101
  CPI1600, // 0b110
};

#define CPI_STEP 38
#define CPI_MIN (16 * CPI_STEP)
#define CPI_MAX (127 * CPI_STEP)

uint8_t pmw3610_serial_read(void);
void pmw3610_serial_write(uint8_t reg_addr);
uint8_t pmw3610_read_reg(uint8_t reg_addr);
void pmw3610_write_reg(uint8_t reg_addr, uint8_t data);

const pointing_device_driver_t pmw3610_pointing_device_driver = {
    .init = pmw3610_init,
    .get_report = pmw3610_get_report,
    .set_cpi = pmw3610_set_cpi,
    .get_cpi = pmw3610_get_cpi,
};

void pmw3610_init(void) {
  gpio_write_pin_high(pmw3610_CS_PIN);       // set cs pin high
  gpio_set_pin_output(pmw3610_CS_PIN);       // set cs pin to output
  gpio_write_pin_high(pmw3610_SCLK_PIN);     // set clock pin high
  gpio_set_pin_output(pmw3610_SCLK_PIN);     // setclockpin to output
  gpio_set_pin_input_high(pmw3610_SDIO_PIN); // set datapin input high

  pmw3610_write_reg(REG_CONFIGURATION, 0x80); // reset sensor
  wait_ms(2);

  pmw3610_read_reg(0x00); // read id
  pmw3610_read_reg(0x01); // read id2
  pmw3610_read_reg(0x02);
  pmw3610_read_reg(0x03);
  pmw3610_read_reg(0x04);
  pmw3610_read_reg(0x12);
}

uint8_t pmw3610_serial_read(void) {
  gpio_set_pin_input(pmw3610_SDIO_PIN);
  uint8_t byte = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    gpio_write_pin_low(pmw3610_SCLK_PIN);
    wait_us(1);

    byte = (byte << 1) | gpio_read_pin(pmw3610_SDIO_PIN);

    gpio_write_pin_high(pmw3610_SCLK_PIN);
    wait_us(1);
  }

  return byte;
}

void pmw3610_serial_write(uint8_t data) {
  gpio_write_pin_low(pmw3610_SDIO_PIN);
  gpio_set_pin_output(pmw3610_SDIO_PIN);

  for (int8_t b = 7; b >= 0; b--) {
    gpio_write_pin_low(pmw3610_SCLK_PIN);
    if (data & (1 << b)) {
      gpio_write_pin_high(pmw3610_SDIO_PIN);
    } else {
      gpio_write_pin_low(pmw3610_SDIO_PIN);
    }
    gpio_write_pin_high(pmw3610_SCLK_PIN);
  }

  wait_us(4);
}

report_pmw3610_t pmw3610_read(void) {
  report_pmw3610_t data = {0};

  data.isMotion = pmw3610_read_reg(REG_STAT) &
                  (1 << 7); // check for motion only (bit 7 in field)
  data.x = (int8_t)pmw3610_read_reg(REG_X);
  data.y = (int8_t)pmw3610_read_reg(REG_Y);

  return data;
}

void pmw3610_write_reg(uint8_t reg_addr, uint8_t data) {
  gpio_write_pin_low(pmw3610_CS_PIN); // set cs pin low
  pmw3610_serial_write(0b10000000 | reg_addr);
  pmw3610_serial_write(data);
  gpio_write_pin_high(pmw3610_CS_PIN); // set cs pin high
}

uint8_t pmw3610_read_reg(uint8_t reg_addr) {
  gpio_write_pin_low(pmw3610_CS_PIN); // set cs pin low
  pmw3610_serial_write(reg_addr);
  wait_us(5);
  uint8_t reg = pmw3610_serial_read();
  gpio_write_pin_high(pmw3610_CS_PIN); // set cs pin high

  return reg;
}

void pmw3610_set_cpi(uint16_t cpi) {
  if (cpi < CPI_MIN) {
    cpi = CPI_MIN;
  } else if (cpi > CPI_MAX) {
    cpi = CPI_MAX;
  }
  uint8_t cpival = (cpi + (CPI_STEP >> 1)) / CPI_STEP;

  pmw3610_write_reg(REG_PROTECT, VAL_PROTECT_DISABLE);
  pmw3610_write_reg(REG_CPI_X, cpival);
  pmw3610_write_reg(REG_CPI_Y, cpival);
  pmw3610_write_reg(REG_PROTECT, VAL_PROTECT_ENABLE);
}

uint16_t pmw3610_get_cpi(void) {
  return pmw3610_read_reg(REG_CPI_X) * CPI_STEP;
}

uint8_t read_pid_pmw3610(void) { return pmw3610_read_reg(REG_PID1); }

report_mouse_t pmw3610_get_report(report_mouse_t mouse_report) {
  report_pmw3610_t data = pmw3610_read();
  if (data.isMotion) {
    pd_dprintf("Raw ] X: %d, Y: %d\n", data.x, data.y);

    mouse_report.x = data.x;
    mouse_report.y = data.y;
  }

  return mouse_report;
}

void pointing_device_driver_init(void) { pmw3610_init(); }

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
  return pmw3610_get_report(mouse_report);
}

uint16_t pointing_device_driver_get_cpi(void) { return pmw3610_get_cpi(); }

void pointing_device_driver_set_cpi(uint16_t cpi) { pmw3610_set_cpi(cpi); }