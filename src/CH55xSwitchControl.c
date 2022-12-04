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

__xdata const uint16_t BUTTON_PUSHING_MSEC = 100;

/**
 * @brief USBコントローラーの初期化
 */
void USBInit(void) {
  USBDeviceCfg();
  USBDeviceEndPointCfg();
  USBDeviceIntCfg();
  UEP0_T_LEN = 0;
  UEP1_T_LEN = 0;
  UEP2_T_LEN = 0;

  memset(&controller_report, 0, sizeof(USB_JoystickReport_Input_t));
  controller_report.LX = 128;
  controller_report.LY = 128;
  controller_report.RX = 128;
  controller_report.RY = 128;
  controller_report.Hat = 8;
}

/**
 * @brief コントローラーの状態をSwitchに送信する
 */
void sendReport(void) {
  uint8_t *p = (uint8_t *)&controller_report;
  for (uint8_t i = 0; i < 8; i++) {
    Ep1Buffer[i + 64] = p[i];
  }
  UEP1_T_LEN = 8;
  UEP1_CTRL = UEP1_CTRL & ~MASK_UEP_T_RES | UEP_T_RES_ACK;
}

void pressButton(uint16_t button) {
  controller_report.Button |= button;
  sendReport();
}

void releaseButton(uint16_t button) {
  controller_report.Button &= ~button;
  sendReport();
}

void pressHatButton(uint8_t hat) {
  controller_report.Hat = hat;
  sendReport();
}

void releaseHatButton(void) {
  controller_report.Hat = 8;
  sendReport();
}

void setStickTiltRatio(uint8_t lx_per, uint8_t ly_per, uint8_t rx_per, uint8_t ry_per) {
  controller_report.LX = (uint8_t)(lx_per * 0xFF / 200 + 0x80);
  controller_report.LY = (uint8_t)(ly_per * 0xFF / 200 + 0x80);
  controller_report.RX = (uint8_t)(rx_per * 0xFF / 200 + 0x80);
  controller_report.RY = (uint8_t)(ry_per * 0xFF / 200 + 0x80);
  sendReport();
}

/**
 * @brief Switchコントローラーのボタンを押す
 * 
 * @param button 押すボタン
 * @param delay_after_pushing_msec ボタンを押し終えた後の待ち時間
 */
void pushButton(uint16_t button, uint32_t delay_time_msec) {
  pressButton(button);
  delay(BUTTON_PUSHING_MSEC);
  releaseButton(button);
  delay(delay_time_msec);
  delay(BUTTON_PUSHING_MSEC);
}

/**
 * @brief Switchコントローラーのボタンを複数回押す
 * 
 * @param button 押すボタン
 * @param delay_after_pushing_msec ボタンを押し終えた後の待ち時間 
 * @param loop_num ボタンを押す回数
 */
void pushButtonLoop(uint16_t button, uint32_t delay_time_msec, uint16_t loop_num) {
  for (uint32_t i = 0; i < loop_num; i++) {
    pressButton(button);
    delay(BUTTON_PUSHING_MSEC);
    releaseButton(button);
    delay(delay_time_msec);
  }
  delay(BUTTON_PUSHING_MSEC);
}

/**
 * @brief Switchコントローラーの矢印ボタンを押す
 * 
 * @param button 押す矢印ボタン
 * @param delay_after_pushing_msec ボタンを押し終えた後の待ち時間
 */
void pushHatButton(uint8_t hat, uint32_t delay_time_msec) {
  pressHatButton(hat);
  delay(BUTTON_PUSHING_MSEC);
  releaseHatButton();
  delay(delay_time_msec);
  delay(BUTTON_PUSHING_MSEC);
}

/**
 * @brief Switchコントローラーの矢印ボタンを複数回押す
 * 
 * @param button 押す矢印ボタン
 * @param delay_after_pushing_msec ボタンを押し終えた後の待ち時間 
 * @param loop_num ボタンを押す回数
 */
void pushHatButtonLoop(uint8_t hat, uint32_t delay_time_msec, uint16_t loop_num) {
  for (uint32_t i = 0; i < loop_num; i++) {
    pressHatButton(hat);
    delay(BUTTON_PUSHING_MSEC);
    releaseHatButton();
    delay(delay_time_msec);
  }
  delay(BUTTON_PUSHING_MSEC);
}

/**
 * @brief Switchコントローラーの矢印ボタンを指定時間の間押し続ける
 * 
 * @param button 押す矢印ボタン
 * @param pushing_time_msec ボタンを押す時間の長さ
 */
void pushHatButtonContinuous(uint8_t hat, uint32_t pushing_time_msec) {
  pressHatButton(hat);
  delay(pushing_time_msec);
  releaseHatButton();
  delay(BUTTON_PUSHING_MSEC);
}

/**
 * @brief Switchのジョイスティックの倒し量を設定する
 * 
 * @param lx_per LスティックのX方向倒し量[％] -100~100の範囲で設定
 * @param ly_per LスティックのY方向倒し量[％] -100~100の範囲で設定
 * @param rx_per RスティックのX方向倒し量[％] -100~100の範囲で設定
 * @param ry_per RスティックのY方向倒し量[％] -100~100の範囲で設定
 * @param tilt_time_msec スティックを倒し続ける時間
 */
void tiltJoystick(uint8_t lx_per, uint8_t ly_per, uint8_t rx_per, uint8_t ry_per, uint32_t tilt_time_msec) {
  setStickTiltRatio(lx_per, ly_per, rx_per, ry_per);
  delay(tilt_time_msec);
  setStickTiltRatio(0, 0, 0, 0);
  delay(BUTTON_PUSHING_MSEC);
}