# Chrysler Town and Country VES display support for OEM/Android multimedia

When original multimedia is replaced, VES displays stops working - they only display white screen
and does not display video from any source.

The aim of this project is change that. 

VERY EARLY ACCESS, MORE INFORMATION will be added later on.

# Brief overview

Original car multimedia and VES displays communicated using CAN protocol. When multimedia is removed, VES is left
in a state waiting for answers which it never receives. To solve this, arduino microprocessor is used to fake
multimedia signals and imitate the behaviour of multimedia. The aim is to make VES think that AUX/DVD is playing and it
should display signal from that source.

# What you need

List of items used to make this work:
* **Arduino microcontroller** or alternative (any should work, but connection to MCP2515 will differ)
* **MCP2515 CAN Bus Module** (I used one from aliexpress for couple of EUR)
* Wires to connect everything up
* Tulip connector (to connect android video out to VES)

I used Arduino pro micro as I had it lying around and because of it's small size, but any arduino or alternative 
should work. Have in mind that connection to MCP2515 will probably be different.

# Steps

* Connect Arduino to MCP2515
* Flash Arduino with provided source code
* Connect MCP2515 to car's CAN bus lane
* Connect Arduino to 5v or USB port (can use multimedia usb port, phone charger etc.)
* Cut video out wires from VES DVD and connect video out signal from multimedia.

# Supported Vehicles

I own and work on **VW Routan 2011** with MyGig NTG4 RHR radio, but it should be identical to:

* Chrysler Town and Country
* Dodge Caravan
* Lancia Voyager
* VW Routan

It might need some adjustments depending on the year and what multimedia type is used.

# Sources

Biggest Thanks for making this project possible goes to Adam Varga as his project shows how to read/write to CAN bus.
https://github.com/adamtheone/canDrive?tab=readme-ov-file

This project also made life easier on figuring out CAN signal meaning. Newer multimedia version has some differences,
but was still very relevant.
https://github.com/BiggRanger/Chrysler-CANBUS-RES-Radio-Interface

Original connector's pinout (same for town country)
https://jeepspecs.com/models/jeep-grand-cherokee/jeep-grand-cherokee-wk/audio-system-wiring/

Pinout for Android multimedia
https://www.tacomaworld.com/threads/wiring-r-r-and-r-l-rca-outputs-android-10-radio-head-units-uis7862.769847/

Arduino pro micro pinout
https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/hardware-overview-pro-micro

Arduino CAN library
https://github.com/sandeepmistry/arduino-CAN
