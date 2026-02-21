# cool655tb


![](img/img00001.jpg)

## What is cool655tb?

cool655tb is 50% splite keyboards with trackball and rotary endoder.
<br>
cool655tb use Low profile keyswitches and keycaps.
<br>
cool655tb use seeed RP2040-Zero,run qmk_firmware.
<br>
<br>

## firmware

cool655tb change keymap by [vial](https://vial.rocks/)

https://github.com/telzo2000/cool655tb/tree/main/firmware

<br>      
Note
<br>

https://sizu.me/m_ki/posts/vef80k39vo23

ご自身の環境でビルドする場合、参考にしてください。

<br>

## buildguide

https://github.com/telzo2000/cool655tb/blob/main/buildguide_for_cool655tb.md


<b>Main steps</b>

1 Soldering switchsocket.
![](img/img00007.jpg)

[Switch socketハンダ付け動画](https://youtu.be/ZnbgaueMR4w?si=_JLjD--3HJJ5Pu7Q)

<br>

2 Soldering RP2040-Zero and pmw3610.
![](img/img00008.jpg)
![](img/img00009.jpg)
![](img/img00010.jpg)

[RP2040-Zeroのハンダ付け動画](https://youtu.be/FV4INvCWlU0)
<br>

3 Pass the shaft through the bearing and attach it to the trackball case.

4 Secure the trackball case to the right top case using screws and nuts.

5 Insert the switch socket into the top plate and then the PCB.

6 Insert the bottom case.

7 Insert the screw from above and secure it with the nut on the bottom case side.

8 Connect to your PC with a USB cable and install the firmware by dragging and dropping.



![](img/img00002.jpg)

<br>

## BOM

<b>common parts</b>
| No. | Patrs | Quantity | remarks | Suppliers | Cost |
|--|--|--|--|--|--|
|番号|名前|数|備考|調達先|参考価格（送料込）|<br>
|1|PCB|2||[JLCPCB](https://jlcpcb.com)||<br>
|2|Top plate|2|3D Print|||
|3|Bottom case|2|3D Print|||
|4|trackball case|1|3D Print|||
|5|Diode<br>ダイオード|56|SMD、PCBA済み|[遊舎工房](https://yushakobo.jp)<br>[Talp Keyboard](https://talpkeyboard.net)<br>[Daily Craft Keyboard](https://shop.dailycraft.jp)等|100個で220円程度から|
|6|Swith socket<br>スイッチソケット|55|choc|[遊舎工房](https://yushakobo.jp)<br>[Talp Keyboard](https://talpkeyboard.net)<br>[Daily Craft Keyboard](https://shop.dailycraft.jp)等|10個で165円程度|
|7|RP2040-Zero|2|MCU Board|[Talp keyboard](https://shop.talpkeyboard.com/products/rp2040-zero-usb-c-compatible)[Waveshare](https://www.waveshare.com/rp2040-zero.htm)|400円ぐらい|
|8|pmw3610|1|trackball senser|[Talp Keyboard](https://talpkeyboard.net)|800円程度|
|9|Rotaly encoder|EC12|[遊舎工房](https://yushakobo.jp)|330円程度|
|10|Screw<br>ネジ|11|なべこねじM2 6mm|[遊舎工房](https://shop.yushakobo.jp/products/a0800s2?variant=37665432535201)|50本880円
|11|Nut<br>ナット|11|M2ネジに付属していることが多い|DIY shop||
|12|Keycap<br>キーキャップ|55|ロープロが最適|[遊舎工房](https://yushakobo.jp)<br>[Talp Keyboard](https://talpkeyboard.net)<br>[Daily Craft Keyboard](https://shop.dailycraft.jp)||
|13|Trackball|1|34mm|||
|14|Bearing|3|外径5mm、内径2mm、幅2.5mm|[amazon](https://www.amazon.co.jp/dp/B0CV7XLDYP?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)||
|15|Shaft|3|径2mm、｜長さ6mm|[amazon](https://www.amazon.co.jp/dp/B0FNMC8BSD?ref=ppx_yo2ov_dt_b_fed_asin_title)|| 
<br>


In addition, USB cable, etc. are required.
<br>
この他に、TRRSケーブルやUSBケーブル等が必要です。
<br>

<br>






# license

[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.ja)

![](img/by-nc-sa.png)
