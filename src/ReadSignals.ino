// Developer:
//        Adam Varga, 2020, All rights reserved.
// Licence:
//        Licenced under the MIT licence. See LICENCE file in the project root.
// Usage of this code:
//        This code creates the interface between the car
//        and the canSniffer_GUI application. If the RANDOM_CAN
//        define is set to 1, this code is generating random
//        CAN packets in order to test the higher level code.
//        The received packets will be echoed back. If the
//        RANDOM_CAN define is set to 0, the CAN_SPEED define
//        has to match the speed of the desired CAN channel in
//        order to receive and transfer from and to the CAN bus.
//        Serial speed is 250000baud <- might need to be increased.
// Required arduino packages:
//        - CAN by Sandeep Mistry (https://github.com/sandeepmistry/arduino-CAN)
// Required modifications:
//        - MCP2515.h: 16e6 clock frequency reduced to 8e6 (depending on MCP2515 clock)
//        - MCP2515.cpp: extend CNF_MAPPER with your desired CAN speeds
//------------------------------------------------------------------------------
#include <CAN.h>
//------------------------------------------------------------------------------
// Settings
#define CAN_SPEED (125E3)
#define CAN_HEADER_SPEED (8E6)
#define SERIAL_BOUND (250000)
//------------------------------------------------------------------------------
// Inits, globals
typedef struct {
  long id;
  byte rtr;
  byte ide;
  byte dlc;
  byte dataArray[20];
} packet_t;

const char SEPARATOR = ',';
const char TERMINATOR = '\n';
const char RXBUF_LEN = 100;

//------------------------------------------------------------------------------
// Printing a packet to serial
void printHex(long num) {
  if ( num < 0x10 ){ Serial.print("0"); }
  Serial.print(num, HEX);
}

void printPacket(packet_t * packet) {
  // packet format (hex string): [ID],[RTR],[IDE],[DATABYTES 0..8B]\n
  // example: 014A,00,00,1A002B003C004D\n
  printHex(packet->id);
  Serial.print(SEPARATOR);
  printHex(packet->rtr);
  Serial.print(SEPARATOR);
  printHex(packet->ide);
  Serial.print(SEPARATOR);
  for (int i = 0; i < packet->dlc; i++) {
    printHex(packet->dataArray[i]);
  }
  Serial.print(TERMINATOR);
}
//------------------------------------------------------------------------------
// CAN RX, TX
void onCANReceive(int packetSize) {
  packet_t rxPacket;
  rxPacket.id = CAN.packetId();
  rxPacket.rtr = CAN.packetRtr() ? 1 : 0;
  rxPacket.ide = CAN.packetExtended() ? 1 : 0;
  rxPacket.dlc = CAN.packetDlc();
  byte i = 0;
  while (CAN.available()) {
    rxPacket.dataArray[i++] = CAN.read();
    if (i >= (sizeof(rxPacket.dataArray) / (sizeof(rxPacket.dataArray[0])))) {
      break;
    }
  }
  printPacket(&rxPacket);
}

void sendPacketToCan(packet_t * packet) {
  for (int retries = 10; retries > 0; retries--) {
    bool rtr = packet->rtr ? true : false;
    if (packet->ide){
      CAN.beginExtendedPacket(packet->id, packet->dlc, rtr);
    } else {
      CAN.beginPacket(packet->id, packet->dlc, rtr);
    }
    CAN.write(packet->dataArray, packet->dlc);
    if (CAN.endPacket()) {
      // success
      break;
    } else if (retries <= 1) {
      return;
    }
  }
}
//------------------------------------------------------------------------------
// Serial parser
char getNum(char c) {
  if (c >= '0' && c <= '9') { return c - '0'; }
  if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
  if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
  return 0;
}

char * strToHex(char * str, byte * hexArray, byte * len) {
  byte *ptr = hexArray;
  char * idx;
  for (idx = str ; *idx != SEPARATOR && *idx != TERMINATOR; ++idx, ++ptr ) {
    *ptr = (getNum( *idx++ ) << 4) + getNum( *idx );
  }
  *len = ptr - hexArray;
  return idx;
}

void rxParse(char * buf, int len) {
  packet_t rxPacket;
  char * ptr = buf;

  byte idTempArray[8], tempLen;
  ptr = strToHex(ptr, idTempArray, &tempLen);
  rxPacket.id = 0;
  for (int i = 0; i < tempLen; i++) {
    rxPacket.id |= (long)idTempArray[i] << ((tempLen - i - 1) * 8);
  }

  ptr = strToHex(ptr + 1, &rxPacket.rtr, &tempLen);
  ptr = strToHex(ptr + 1, &rxPacket.ide, &tempLen);
  ptr = strToHex(ptr + 1, rxPacket.dataArray, &rxPacket.dlc);

  sendPacketToCan(&rxPacket);
}

void RXcallback(void) {
  static int rxPtr = 0;
  static char rxBuf[RXBUF_LEN];
  int packetSize = CAN.parsePacket();

  while (Serial.available() > 0) {
    if (rxPtr >= RXBUF_LEN) {
      rxPtr = 0;
    }
    char c = Serial.read();
    rxBuf[rxPtr++] = c;
    if (c == TERMINATOR) {
      rxParse(rxBuf, rxPtr);
      rxPtr = 0;
    }
  }
}

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(SERIAL_BOUND);
  while (!Serial) {
    ; // wait for serial port to connect.
  }

  CAN.setClockFrequency(CAN_HEADER_SPEED);
  if (!CAN.begin(CAN_SPEED)) {
    while (1);
  }

  CAN.onReceive(onCANReceive);
}

void loop() {
  RXcallback();
}
