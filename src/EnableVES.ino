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
void MyGigSimulation(void) {
  canSend(0x3B0,0x0B,0x10,0x01,0x01,0x01,0x13,0x87,0x01);
  delay(5000);
}

void SendInitPackets(void) {
  canSend(0x3FB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
  canSend(0x3C0,0xFF,0x00);
  canSend(0x3B3,0x08,0x00,0x00,0x11,0x0F,0x00,0x00,0x00);
  canSend(0x3B0,0x04,0x10,0x01,0x01,0x01,0x13,0x9D,0x00);
  canSend(0x3A4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
  canSend(0x392,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
  canSend(0x2E9,0x00,0x00,0x00,0x00);
  canSend(0x2D4,0x00,0x00,0x00,0x00,0x0F,0xFF);
  canSend(0x306,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
  canSend(0x2D0,0x00,0x00,0x00,0xF0,0x01);
  canSend(0x290,0x00,0xBB,0x00,0x0F,0x07,0x00,0x00,0x00);
  canSend(0x416,0xFD,0x1B,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF);
  canSend(0x293,0x50,0x00,0x01,0x21,0x02,0x00,0x00,0x11);
  canSend(0x294,0x09,0x06,0x00,0x00,0x00,0x00,0x00,0x00);
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
}

void canSend(uint32_t ID, uint8_t b0)
{
  uint8_t b[1];
  b[0] = b0;
  canTX(1, ID, b);
}
void canSend(uint32_t ID, uint8_t b0, uint8_t b1)
{
  uint8_t b[2];
  b[0] = b0; b[1] = b1;
  canTX(2, ID, b);
}
void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2)
{
  uint8_t b[3];
  b[0] = b0; b[1] = b1; b[2] = b2;
  canTX(3, ID, b);
}
void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
{
  uint8_t b[4];
  b[0] = b0; b[1] = b1; b[2] = b2; b[3] = b3;
  canTX(4, ID, b);
}
void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
  uint8_t b[5];
  b[0] = b0; b[1] = b1; b[2] = b2; b[3] = b3; b[4] = b4;
  canTX(5, ID, b);
}
void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5)
{
  uint8_t b[6];
  b[0] = b0; b[1] = b1; b[2] = b2; b[3] = b3; b[4] = b4; b[5] = b5;
  canTX(6, ID, b);
}
void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6)
{
  uint8_t b[7];
  b[0] = b0; b[1] = b1; b[2] = b2; b[3] = b3; b[4] = b4; b[5] = b5; b[6] = b6;
  canTX(7, ID, b);
}
void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7)
{
  uint8_t b[8];
  b[0] = b0; b[1] = b1; b[2] = b2; b[3] = b3; b[4] = b4; b[5] = b5; b[6] = b6; b[7] = b7;
  canTX(8, ID, b);
}

void canTX(uint8_t packetSize, uint32_t ID, uint8_t b[])
{
  CAN.beginPacket(ID, packetSize);
  CAN.write(b, packetSize);
  CAN.endPacket();
}
