# What each code means

Multimedia is sending multiple signals to CANBUS. Currently code sends all the signals which multimedia sends when it is 
turned on, and repeats only the one which is relevant for VES.

## Codes

```
ID  RT ID DL D0 D1 D2 D3 D4 D5 D6 D7
3B0 00 00 08 XX 10 00 00 00 13 87 01

06 - AUX
05 - HDD
08 - BT
09 - SAT
0B - VES DISK
0D - VES AUX 1
0E - VES AUX 2
0F - TV

Last digints (D5 D6 D7) 13 87 01 - seems to be radio bandwith (90.3) in this case.
```

## Buttons from VES remote control

VES remote control can be programmed to trigger various actions - increase volume, skip to the next movie etc.

When any button is pressed on remote control, following CANBUS signal is fired:
```
ID  RT ID DL D0 D1 D2 D3 D4 D5 D6 D7
3A1 00 00 08 00 55 00 07 00 00 00 07

D3 - 05
D4 - xx

1B - MENU
01 - Next
02 - Prev
03 - Rewing
04 - Forward
5A - ENTER
09 - Program up
0A - Program down
14/13 - Play/Stop
59 - Status
15 - Stop
```

Have in mind that these codes are NOT fired when AUX input is selected. Then only the  menu button gives a signal.

When these signals are caught by arduino, it can send wheel buttons signal to CANBUS, which will be caught by android
canbus and alter the sound on it. If no android multimedia is present, it is also possible to enable and control 
amplifier with CANBUS signals.

Amplifier control signal:
```
ID  RT ID DL D0 D1 D2 D3 D4 D5 D6 D7
3D9 00 0A 0A 0A 0A 0A 00
```


## Additional info

```
ID  RT ID DL D0 D1 D2 D3 D4 D5 D6 D7
293 00 00 08 40 00 01 21 02 00 06 16 

D6 D7 shows video time in seconds. In this case 06 16 = 1566 seconds = 26 minutes 6 seconds.
```
