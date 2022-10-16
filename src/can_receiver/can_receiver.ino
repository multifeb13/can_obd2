#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN(10);

void setup() {
    Serial.begin(115200);
    if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
        CAN.setMode(MCP_NORMAL);
    } else {
        Serial.println("Can init fail");
    }
}

void loop() {
    unsigned long id;
    byte len;
    byte buf[8];

    if (CAN.checkReceive() == CAN_MSGAVAIL) {
        CAN.readMsgBuf(&id, &len, buf);
        Serial.print("ID:");
        Serial.print(id);
        Serial.print(" DATA");
        for (byte i = 0; i < len; i++) {
            Serial.print(":");
            Serial.print(buf[i], HEX);
        }
        Serial.println();
    }
}
