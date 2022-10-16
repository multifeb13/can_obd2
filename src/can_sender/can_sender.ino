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
    static byte buf[] = {0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    CAN.sendMsgBuf(0x02, 0, 8, buf);  // ID:0x02, 標準フレーム:0, データ長:8
    delay(1000);
}
