#include <stdint.h>
#include "include/ch5xx.h"
#include "include/ch5xx_usb.h"

#define BUTTON_NONE 0x0000
#define BUTTON_Y 0x0001
#define BUTTON_B 0x0002
#define BUTTON_A 0x0004
#define BUTTON_X 0x0008
#define BUTTON_L 0x0010
#define BUTTON_R 0x0020
#define BUTTON_ZL 0x0040
#define BUTTON_ZR 0x0080
#define BUTTON_MINUS 0x0100
#define BUTTON_PLUS 0x0200
#define BUTTON_LCLICK 0x0400
#define BUTTON_RCLICK 0x0800
#define BUTTON_HOME 0x1000
#define BUTTON_CAPTURE 0x2000

#define HAT_UP 0x00
#define HAT_UP_RIGHT 0x01
#define HAT_RIGHT_UP 0x01
#define HAT_RIGHT 0x02
#define HAT_DOWN_RIGHT 0x03
#define HAT_RIGHT_DOWN 0x03
#define HAT_DOWN 0x04
#define HAT_DOWN_LEFT 0x05
#define HAT_LEFT_DOWN 0x05
#define HAT_LEFT 0x06
#define HAT_UP_LEFT 0x07
#define HAT_LEFT_UP 0x07
#define HAT_CENTER 0x08

typedef struct {
  uint16_t Button;
  uint8_t Hat;
  uint8_t LX;
  uint8_t LY;
  uint8_t RX;
  uint8_t RY;
  uint8_t VendorSpec;
} USB_JoystickReport_Input_t;

void USBInit(void);
void sendReport(void);
void pressButton(uint16_t button);
void releaseButton(uint16_t button);
void pressHatButton(uint8_t hat);
void releaseHatButton(void);
void setStickTiltRatio(uint8_t lx_per, uint8_t ly_per, uint8_t rx_per, uint8_t ry_per);
void pushButton(uint16_t button, uint32_t delay_time_msec);
void pushButtonLoop(uint16_t button, uint32_t delay_time_msec, uint16_t loop_num);
void pushButtonContinuous(uint16_t button, uint32_t pushing_time_msec);
void pushHatButton(uint8_t hat, uint32_t delay_time_msec);
void pushHatButtonLoop(uint8_t hat, uint32_t delay_time_msec, uint16_t loop_num);
void pushHatButtonContinuous(uint8_t hat, uint32_t pushing_time_msec);
void tiltJoystick(uint8_t lx_per, uint8_t ly_per, uint8_t rx_per, uint8_t ry_per, uint32_t tilt_time_msec);