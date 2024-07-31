# What each code means

Multimedia is sending multiple signals to CANBUS. Currently code sends all the signals which multimedia sends when it is 
turned on, and repeats only the one which is relevant for VES.

## Codes

```
ID 0x291
RT ID DL D0 D1 D2 D3 D4 D5 D6 D7
00 00 08 **xx** 10 00 00 00 12 12 01

06 - AUX
05 - HDD
08 - BT
09 - SAT
0B - VES DISK
0D - VES AUX 1
0E - VES AUX 2
0F - TV
```

## Buttons from VES remote control

VES remote control can be programmed to trigger various actions - increase volume, skip to the next movie etc.

When any button is pressed on remote control, following CANBUS signal is fired:
```
ID  RT ID DL D0 D1 D2 D3 D4 D5 D6 D7
3A1 00 00 08 00 55 00 07 00 00 00 07

D3 - 05
D4 - xx

01 - next
02 - prev
03 rewing
04 forward
5A - ENTER
09 - prog up
0A - prog down
14/13 - play stop
59 - status
15 stop
1B - MENU
```

When these signals are caught by arduino, it can send wheel buttons signal to CANBUS, which will be caught by android
canbus and alter the sound on it. If no android multimedia is present, it is also possible to enable and control 
amplifier with CANBUS signals.

Amplifier control signal:
```
ID  RT ID DL D0 D1 D2 D3 D4 D5 D6 D7
3D9 00 0A 0A 0A 0A 0A 00
```

