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

#include "rm67162.h"
#include "cockpit_var.h"

#include "tftespi_cn_fonts.h"
#include "tftespi_en_fonts.h"
#include "j20_109_182.h" //歼20图标
#include "salt_45_43.h" //GPS卫星图标



// 双核运行所需handle，用于追踪执行情况
TaskHandle_t Task1;
TaskHandle_t Task2;


TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);  // Declare Sprite object "spr" with pointer to "tft" object
TFT_eSprite spr_meters = TFT_eSprite(&tft);
TFT_eSprite spr_meters_2 = TFT_eSprite(&tft);
TFT_eSprite spr_jet = TFT_eSprite(&tft);
TFT_eSprite spr_status = TFT_eSprite(&tft);
TFT_eSprite spr_left_bar = TFT_eSprite(&tft);
TFT_eSprite spr_left_rec = TFT_eSprite(&tft);
TFT_eSprite spr_right_bar = TFT_eSprite(&tft);
TFT_eSprite spr_right_rec = TFT_eSprite(&tft);
TFT_eSprite spr_mid = TFT_eSprite(&tft);


//定义下方副显示屏（2号屏）的虚拟对象，起名u8g2。无法同时开启两个硬件I2C协议，用软件I2C。FPS较低。
U8G2_SSD1306_72X40_ER_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 41, /* data=*/ 40, /* reset=*/ U8X8_PIN_NONE);  


//定义最上方副显示屏（1号屏）的虚拟对象，起名u8g1。1号屏用硬件I2C协议，FPS高，用于显示电流数据。
U8G2_SSD1306_96X16_ER_F_HW_I2C u8g1(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 1, /* data=*/ 2);


void setup() {

  rm67162_init(); 
  lcd_setRotation(1);  
  u8g1.begin();
  u8g2.begin();
  u8g1.enableUTF8Print();
  u8g2.enableUTF8Print();

  u8g1.setFont(u8g2_font_wqy16_t_gb2312b);
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);

  Serial.begin(115200);
  Serial.setRxBufferSize(2048); // 增加接收缓冲区大小

  spr.createSprite(165, 240);  //attitude indicator
  spr_meters.createSprite(80, 240);
  spr_meters_2.createSprite(80, 240);
  spr_jet.createSprite(109, 182);
  spr_mid.createSprite(200, 240);
  spr_status.createSprite(109, 53);
  spr_right_bar.createSprite(50, 180);
  spr_left_bar.createSprite(50, 180);
  spr_right_rec.createSprite(80, 40);
  spr_left_rec.createSprite(80, 40);


xTaskCreatePinnedToCore(
                  Task1code,   /* Task function. */
                  "Task1",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  1,           /* priority of the task */
                  &Task1,      /* Task handle to keep track of created task */
                  0);          /* pin task to core 0 */     


  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */

}

/*
// task1code, 显示主显示屏信息
void Task1code( void * pvParameters ){
  //task 的时间不能太短，否则会触发task watchdog,导致芯片重启
  // Serial.print("Task1 begines on core ");
  // Serial.println(xPortGetCoreID());
  for(;;){
    vTaskDelay(1); //disable task watchdog
    // Serial.print("Task1 running on core ");
    // Serial.println(xPortGetCoreID());

    push_main_screen();
    adjust_brightness_main();

    // 计算主屏幕fps0
    frameCount0 ++;
    now0 = millis();
    if (now0 - Millis0 >= 2000){
      fps0 = frameCount0/2;
      frameCount0 = 0;   
      Millis0 = now0;      
    }      
  } 
}*/
void Task1code(void * pvParameters) {
  const uint32_t UPDATE_INTERVAL = 20; // 50Hz (1000ms/50 = 20ms)
  uint32_t previousMillis = 0;
  
  for(;;) {
    uint32_t currentMillis = millis();
    
    // 检查是否到达更新间隔
    if(currentMillis - previousMillis >= UPDATE_INTERVAL) {
      previousMillis = currentMillis;
      
      // 获取并处理MAVLink数据
      get_mavlink_data();
      
      // 更新显示
      push_main_screen();
      adjust_brightness_main();

      // 计算FPS
      frameCount0++;
      now0 = currentMillis;
      if (now0 - Millis0 >= 2000) {
        fps0 = frameCount0/2;
        frameCount0 = 0;   
        Millis0 = now0;      
      }
    }
    
    vTaskDelay(1); // 防止看门狗复位
  }
}
// Task2code: 显示1、2屏幕信息
void Task2code( void * pvParameters ){

  for(;;){
    vTaskDelay(1);
    // Serial.print("Task2 running on core ");
    // Serial.println(xPortGetCoreID());
    push_u8g1();
    adjust_brightness_small();

    now1 = millis();
    frameCount1 ++;
    if (now1 - Millis1st >= 1000){
      fps1 = frameCount1;
      frameCount1 = 0;   
      Millis1st = now1;

      push_u8g2();
    }
  }
}

void loop(void) {  
  
} // void loop
