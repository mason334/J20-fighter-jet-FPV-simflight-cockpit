#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <MAVLink.h>
#include "TFT_eSPI.h"
#include <math.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>  //hardware I2C need this library
#endif

#include "hud_var.h"


//抬头显示器定义u8g3 HUD
U8G2_SSD1327_WS_128X128_F_4W_HW_SPI u8g3(U8G2_R3, /* cs=*/ 10, /* dc=*/ 46, /* reset=*/ 3); //硬件SPI，这个定义刷新速度快
// U8G2_SSD1327_WS_128X128_F_4W_SW_SPI u8g3(U8G2_R3, /* clock=*/12, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 42, /* reset=*/ 43); //软件SPI，这个定义刷新速度较慢。不推荐使用。



void setup() {

  u8g3.begin();
  u8g3.sendF("ca", 0xa0, 0x41); //镜像显示内容
  u8g3.enableUTF8Print();
  u8g3.setFont(u8g2_font_wqy16_t_gb2312b);
  Serial.begin(57600);
}



void loop(void) {  
  push_u8g3();
  adjust_brightness();

    // 计算主屏幕fps0
  frameCount0 ++;
  now0 = millis();
  if (now0 - Millis0 >= 2000){
    fps0 = frameCount0/2;
    frameCount0 = 0;   
    Millis0 = now0;
  }   

} // void loop
