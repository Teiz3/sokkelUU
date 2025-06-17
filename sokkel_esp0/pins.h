//============================ I2C pins ================================
#define SDA_PIN 21
#define SCL_PIN 38

//=========================== Status LEDs pins ========================
#define STATUS_MCP_ADDR 0x20

#define STATUS_LED_A1 0   //A0
#define STATUS_LED_A2 1
#define STATUS_LED_A3 2
#define STATUS_LED_A4 3

#define STATUS_LED_B1 4
#define STATUS_LED_B2 5
#define STATUS_LED_B3 6
#define STATUS_LED_B4 7

#define STATUS_LED_C1 8   // B0
#define STATUS_LED_C2 9
#define STATUS_LED_C3 10
#define STATUS_LED_C4 11

#define STATUS_LED_D1 12
#define STATUS_LED_D2 13
#define STATUS_LED_D3 14
#define STATUS_LED_D4 15

//============================ Contacts pins ========================
#define CONTACT_MCP_ABC_ADDR 0x22

#define CONTACT_A1 1  //A0
#define CONTACT_A2 0
#define CONTACT_A3 13
#define CONTACT_A4 14
#define CONTACT_A5 15

#define CONTACT_B1 7
#define CONTACT_B2 6
#define CONTACT_B3 5
#define CONTACT_B4 4    //B0
#define CONTACT_B5 3

#define CONTACT_C1 8
#define CONTACT_C2 9
#define CONTACT_C3 10
#define CONTACT_C4 11
#define CONTACT_C5 12

// Side D on sepperate MCP27008
#define CONTACT_MCP_D_ADDR 0x27

#define CONTACT_D1 0
#define CONTACT_D2 1
#define CONTACT_D3 2
#define CONTACT_D4 3
#define CONTACT_D5 4

//============================== Marble track pins ===================
#define MARBLE_SERVO_1 16//2
#define MARBLE_SERVO_2 4
#define MARBLE_SERVO_3 5

#define MARBLE_LED_1 6
#define MARBLE_LED_2 7
#define MARBLE_LED_3 8

#define LOCK_OUT 40
#define LOCK_LED 39