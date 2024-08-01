# Step by step guide

Following these steps you should have a working second row display working with any multimedia system.
This was only tested on VW Routan with MyGig NTG4 RHR radio, but it should work for other 
Chrysler based versions as well (Dodge Caravan, Lancia Voyager etc).

* Buy Arduino Pro Micro and MCP2515 CAN Bus Module
* Connect Arduino to MCP2515
  * [schematics will be provided here]
* Flash Arduino with provided source code from [EnableVES.ino](src%2FEnableVES.ino)
  * Download Arduino IDE
  * Connect Arduino to PC via USB cable
  * In Arduino IDE Select Arduino Leonardo if not already selected
  * Install CAN library
    * Press on library icon in Arduino IDE
    * Search for 'Sandeep Mistry' and select CAN library
  * Press Upload button in Arduino IDE
  * If all goes well and there are no errors, Arduino should be ready to go
* Connect MCP2515 + and - to car's CAN bus lane
  * [schematics will be provided here], for now refer to links provided in readme
* Connect Arduino to phone charger, multimedia USB or any other 5v source
* Connect Multimedia video OUT to VES DVD video OUT
  * Take out VES DVD player and cut off video out signal and ground wires
  * Connect video out signal from multimedia to VES video out signal cables
  * [schematics will be provided here]
  * Connect VES DVD player back 

And you are done. You should now see output from multimedia system on VES display.

This has worked for me, if you have a different original unit your mileage might vary - you might need to adjust the 
CANBUS codes.
