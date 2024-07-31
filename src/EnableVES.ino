// Developer: 
//        Aurimas Gladutis, 2024, All rights reserved.
// Licence: 
//        Licenced under the MIT licence. See LICENCE file in the project root.
// Required arduino packages: 
//        - CAN by Sandeep Mistry (https://github.com/sandeepmistry/arduino-CAN)
//------------------------------------------------------------------------------
#include <CAN.h>
//------------------------------------------------------------------------------
#define CAN_SPEED (125E3)
#define CAN_HEADER_SPEED (8E6)
//------------------------------------------------------------------------------
typedef struct {
  long id;
  byte rtr;
  byte ide;
  byte dlc;
  byte dataArray[20];
} packet_t;

int packetsSent = 0;

//------------------------------------------------------------------------------
void MyGigSimulation(void) {
  if (packetsSent == 20) {
    SendInitPackets();
    packetsSent = 0;
  }
  
  byte videoData[] = {0x04,0x28,0x15,0x11,0x15,0x11,0x07};
  sendPacketToCan(0x291, videoData, sizeof(videoData));
  packetsSent = packetsSent + 1;
}

void SendInitPackets(void) {
  byte data[] = {0x00,0xD8,0x00,0x50,0x6F,0x70,0x00,0x00};
  byte data1[] = {0x09,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
  byte data2[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte data3[] = {0x00,0x0A,0x0A,0x0A,0x0A,0x0A,0x00};
  byte data4[] = {0xFF,0x00};
  byte data5[] = {0x08,0x00,0x00,0x11,0x0F,0x00,0x00,0x00};
  byte data6[] = {0x04,0x10,0x01,0x01,0x01,0x13,0x9D,0x00};
  byte data7[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte data8[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  byte data9[] = {0x00,0x00,0x00,0x00};
  byte data10[] = {0x00,0x00,0x00,0x00,0x0F,0xFF};
  byte data11[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
  byte data12[] = {0x00,0x00,0x00,0xF0,0x01};
  byte data13[] = {0x50,0x00,0x01,0x21,0x02,0x00,0x00,0x11};
  byte data15[] = {0x00,0xBB,0x00,0x0F,0x07,0x00,0x00,0x00};
  byte data16[] = {0xFD,0x1B,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF};

  sendPacketToCan(0x3A0, data, sizeof(data));
  sendPacketToCan(0x294, data1, sizeof(data1));
  sendPacketToCan(0x3FB, data2, sizeof(data2));
  sendPacketToCan(0x3D9, data3, sizeof(data3));
  sendPacketToCan(0x3C0, data4, sizeof(data4));
  sendPacketToCan(0x3B3, data5, sizeof(data5));
  sendPacketToCan(0x3B0, data6, sizeof(data6));
  sendPacketToCan(0x3A4, data7, sizeof(data7));
  sendPacketToCan(0x392, data8, sizeof(data8));
  sendPacketToCan(0x2E9, data9, sizeof(data9));
  sendPacketToCan(0x2D4, data10, sizeof(data10));
  sendPacketToCan(0x306, data11, sizeof(data11));
  sendPacketToCan(0x2D0, data12, sizeof(data12));
  sendPacketToCan(0x293, data13, sizeof(data13));
  sendPacketToCan(0x290, data15, sizeof(data15));
  sendPacketToCan(0x416, data16, sizeof(data16));
}

void sendPacketToCan(int id, byte dataArray[], int dlc) {
  for (int retries = 10; retries > 0; retries--) {
    CAN.beginPacket(id, dlc, false);
    CAN.write(dataArray, dlc);
    if (CAN.endPacket()) {
      break;
    } else if (retries <= 1) {
      return;
    }
  }
}

//------------------------------------------------------------------------------
// Setup
void setup() {
  CAN.setClockFrequency(CAN_HEADER_SPEED);
  if (!CAN.begin(CAN_SPEED)) {
    while (1);
  }
  SendInitPackets();
}

void loop() {
  MyGigSimulation();
  delay(50);
}
