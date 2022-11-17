#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "include/ch5xx.h"
#include "include/ch5xx_usb.h"
#include "CH55xSwitchControl.h"
#include "USBconstant.h"
#include "USBhandler.h"

extern __xdata __at(EP1_ADDR)
uint8_t Ep1Buffer[];

__xdata USB_JoystickReport_Input_t controller_report;

__xdata const uint16_t INPUT_TIME = 100;

__xdata const uint16_t INPUT_TIME_TWICE = 200;

/**
 * USBコントローラーの初期化
 */
void USBInit(void) {
  USBDeviceCfg();
  USBDeviceEndPointCfg();
  USBDeviceIntCfg();
  UEP0_T_LEN = 0;
  UEP1_T_LEN = 0;
  UEP2_T_LEN = 0;

  memset(&controller_report, 0, sizeof(USB_JoystickReport_Input_t));
  controller_report.LX = STICK_NEUTRAL;
  controller_report.LY = STICK_NEUTRAL;
  controller_report.RX = STICK_NEUTRAL;
  controller_report.RY = STICK_NEUTRAL;
  controller_report.Hat = HAT_NEUTRAL;
}

/**
 * コントローラーの状態をSwitchに送信する
 */
void sendReport(void) {
  uint8_t *p = (uint8_t *)&controller_report;
  for (uint8_t i = 0; i < 8; i++) {
    Ep1Buffer[i + 64] = p[i];
  }
  UEP1_T_LEN = 8;
  UEP1_CTRL = UEP1_CTRL & ~MASK_UEP_T_RES | UEP_T_RES_ACK;
}

/**
 * ボタンを押す
 *
 * @param uint16_t button     押すボタン
 */
void pressButton(uint16_t button) {
  controller_report.Button |= button;
}

/**
 * ボタンを離す
 */
void releaseButton(uint16_t button) {
  controller_report.Button &= ~button;
}

/**
 * 十字キーを押す
 *
 * @param uint8_t hat 押す十字キーのボタン
 */
void pressHatButton(uint8_t hat) {
  controller_report.Hat = hat;
}

/**
 * 十字キーを離す
 */
void releaseHatButton(void) {
  controller_report.Hat = HAT_NEUTRAL;
}

/**
 * 左スティックを傾ける
 *
 * @param uint8_t lx 左スティックのX軸
 * @param uint8_t ly 左スティックのY軸
 */
void moveLeftStick(uint8_t lx, uint8_t ly) {
  controller_report.LX = lx;
  controller_report.LY = ly;
}

/**
 * 右スティックを傾ける
 *
 * @param uint8_t rx 右スティックのX軸
 * @param uint8_t ry 右スティックのY軸
 */
void moveRightStick(uint8_t rx, uint8_t ry) {
  controller_report.RX = rx;
  controller_report.RY = ry;
}

/**
 * ボタンを押す
 *
 * @param uint16_t button     押すボタン
 * @param uint32_t delay_time ボタンを押した後の待ち時間（1秒 = 1000）
 */
void pushButton(uint16_t button, uint32_t delay_time) {
  pressButton(button);
  sendReport();
  delay(INPUT_TIME);
  releaseButton(button);
  sendReport();
  delay(delay_time);
  delay(INPUT_TIME);
}

/**
 * ボタンを複数回押す
 *
 * @param uint16_t button     押すボタン
 * @param uint32_t delay_time ボタンを押した後の待ち時間（1秒 = 1000）
 * @param uint16_t loop_count ボタンを押す回数
 */
void pushButtonLoop(uint16_t button, uint32_t delay_time, uint16_t loop_count) {
  for (uint32_t i = 0; i < loop_count; i++) {
    pressButton(button);
    sendReport();
    delay(INPUT_TIME);
    releaseButton(button);
    sendReport();
    delay(delay_time);
  }
  delay(INPUT_TIME);
}

/**
 * ボタンを指定の時間押し続ける
 *
 * @param uint16_t button    押し続けるボタン
 * @param uint32_t hold_time ボタンを押す時間の長さ（1秒 = 1000）
 */
void holdButton(uint16_t button, uint32_t hold_time) {
  pressButton(button);
  sendReport();
  delay(hold_time);
  releaseButton(button);
  sendReport();
  delay(INPUT_TIME);
}

/**
 * 十字キーを押す
 *
 * @param uint8_t  hat        押す十字キーのボタン
 * @param uint32_t delay_time ボタンを押した後の待ち時間（1秒 = 1000）
 */
void pushHat(uint8_t hat, uint32_t delay_time) {
  pressHatButton(hat);
  sendReport();
  delay(100);
  releaseHatButton();
  sendReport();
  delay(delay_time);
  delay(INPUT_TIME);
}

/**
 * 十字キーを複数回押す
 *
 * @param uint8_t  hat        押す十字キーのボタン
 * @param uint32_t delay_time ボタンを押した後の待ち時間（1秒 = 1000）
 * @param uint16_t loop_count ボタンを押す回数
 */
void pushHatLoop(uint8_t hat, uint32_t delay_time, uint16_t loop_count) {
  for (uint32_t i = 0; i < loop_count; i++) {
    pressHatButton(hat);
    sendReport();
    delay(INPUT_TIME);
    releaseHatButton();
    sendReport();
    delay(delay_time);
  }
  delay(INPUT_TIME);
}

/**
 * 十字キーを指定の時間押し続ける
 *
 * @param uint8_t  hat       押し続ける十字キーのボタン
 * @param uint32_t hold_time ボタンを押す時間の長さ（1秒 = 1000）
 */
void holdHat(uint8_t hat, uint32_t hold_time) {
  pressHatButton(hat);
  sendReport();
  delay(hold_time);
  releaseHatButton();
  sendReport();
  delay(INPUT_TIME);
}

/**
 * 左スティックを指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t       lx        左スティックのx軸
 * @param uint8_t       ly        左スティックのy軸
 * @param uint32_t      tilt_time スティックを傾ける時間の長さ
 * @param uint16_t      button    連打するボタン
 *
 * @see STICK_MIN       0
 * @see STICK_NEUTRAL 128
 * @see STICK_MAX     255
 */
void tiltLeftStick(uint8_t lx, uint8_t ly, uint32_t tilt_time, uint16_t button) {
  moveLeftStick(lx, ly);
  sendReport();
  if (button) {
    while (INPUT_TIME_TWICE <= tilt_time) {
      pressButton(button);
      sendReport();
      delay(INPUT_TIME);
      releaseButton(button);
      sendReport();
      delay(INPUT_TIME);
      tilt_time -= INPUT_TIME_TWICE;
    }
  }
  delay(tilt_time);
  moveLeftStick(STICK_NEUTRAL, STICK_NEUTRAL);
  sendReport();

  delay(INPUT_TIME);
}

/**
 * 右スティックを指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t       rx        右スティックのx軸
 * @param uint8_t       ry        右スティックのy軸
 * @param uint32_t      tilt_time スティックを傾ける時間の長さ
 * @param uint16_t      button    連打するボタン
 *
 * @see STICK_MIN       0
 * @see STICK_NEUTRAL 128
 * @see STICK_MAX     255
 */
void tiltRightStick(uint8_t lx, uint8_t ly, uint32_t tilt_time, uint16_t button) {
  moveRightStick(lx, ly);
  sendReport();
  if (button) {
    while (INPUT_TIME_TWICE <= tilt_time) {
      pressButton(button);
      sendReport();
      delay(INPUT_TIME);
      releaseButton(button);
      sendReport();
      delay(INPUT_TIME);
      tilt_time -= INPUT_TIME_TWICE;
    }
  }
  delay(tilt_time);
  moveRightStick(STICK_NEUTRAL, STICK_NEUTRAL);
  sendReport();
  delay(INPUT_TIME);
}

/**
 * 左スティックと右スティックを同時に指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t       lx        左スティックのx軸
 * @param uint8_t       ly        左スティックのy軸
 * @param uint8_t       rx        右スティックのx軸
 * @param uint8_t       ry        右スティックのy軸
 * @param uint32_t      tilt_time スティックを傾ける時間の長さ
 * @param uint16_t      button    連打するボタン
 *
 * @see STICK_MIN       0
 * @see STICK_NEUTRAL 128
 * @see STICK_MAX     255
 */
void tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry, uint32_t tilt_time, uint16_t button) {
  moveLeftStick(lx, ly);
  moveRightStick(rx, ry);
  sendReport();
  if (button) {
    while (INPUT_TIME_TWICE <= tilt_time) {
      pressButton(button);
      sendReport();
      delay(INPUT_TIME);
      releaseButton(button);
      sendReport();
      delay(INPUT_TIME);
      tilt_time -= INPUT_TIME_TWICE;
    }
  }
  delay(tilt_time);
  moveLeftStick(STICK_NEUTRAL, STICK_NEUTRAL);
  moveRightStick(STICK_NEUTRAL, STICK_NEUTRAL);
  sendReport();
  delay(INPUT_TIME);
}