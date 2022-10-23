#include <SPI.h>
#include <mcp_can.h>

#define STANDARD_CAN_11BIT 1  // That depands on your car. some 1 some 0.

#if STANDARD_CAN_11BIT
#define CAN_ID_PID 0x7DF
#else
#define CAN_ID_PID 0x18db33f1
#endif

#define PID_ENGIN_PRM 0x0C
#define PID_VEHICLE_SPEED 0x0D
#define PID_COOLANT_TEMP 0x05

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
    byte buf[] = {0x02, 0x01, PID_ENGIN_PRM, 0x00, 0x00, 0x00, 0x00, 0x00};
#if STANDARD_CAN_11BIT
    CAN.sendMsgBuf(CAN_ID_PID, 0, 8,
                   buf);  // ID:0x02, 標準フレーム:0, データ長:8
#else
    CAN.sendMsgBuf(CAN_ID_PID, 1, 8,
                   buf);  // ID:0x02, 標準フレーム:0, データ長:8
#endif

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
