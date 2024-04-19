/*
驱动主屏幕注意事项，请务必阅读
ILI9341 library example
(c) 2020 Pawel A. Hernik
 ILI9341 240x320 2.2" tft pinout (header at the top, from left):

引脚定义如下
GND   -> GND
VCC   -> 3.3V
其他的引脚在Arduino\libraries\TFT_eSPI\User_Setup.h文件中修改
###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP   ######
For ESP32 Dev board (only tested with ILI9341 display)
The hardware SPI can be mapped to any pins
#define TFT_MISO 13
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   10  // Chip select control pin
#define TFT_DC    7  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)
*/


#include <Arduino.h>
#define SCR_WD   240
#define SCR_HT   240

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <MAVLink.h>
#include "TFT_eSPI.h"
#include <math.h>
#include <PNGdec.h>
#include "pictures.h" // Image is stored here in an 8 bit array
#include <U8g2lib.h>
#include "cockpit_var.h"

// 双核运行所需handle，用于追踪执行情况
TaskHandle_t Task1;
TaskHandle_t Task2;

PNG png; // PNG decoder instance

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);  // Declare Sprite object "spr" with pointer to "tft" object
TFT_eSprite spr2 = TFT_eSprite(&tft);  // Declare Sprite object "spr" with pointer to "tft" object
TFT_eSprite spr3 = TFT_eSprite(&tft);
TFT_eSprite spr4 = TFT_eSprite(&tft);
TFT_eSprite spr5 = TFT_eSprite(&tft);
TFT_eSprite spr6 = TFT_eSprite(&tft);

//定义最上方副显示屏（1号屏）的虚拟对象，起名u8g1。
// U8G2_SSD1306_96X16_ER_F_SW_I2C u8g1(U8G2_R0, /* clock=*/ 2, /* data=*/ 42, /* reset=*/ U8X8_PIN_NONE);  
U8G2_SSD1306_96X16_ER_F_HW_I2C u8g1(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 2, /* data=*/ 42); //1号屏用硬件I2C协议，FPS高，用于显示电流数据。

//定义下方副显示屏（2号屏）的虚拟对象，起名u8g2。 无法同时开启两个硬件I2C协议，2号屏用软件I2C协议，FPS较低。
U8G2_SSD1306_72X40_ER_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 20, /* data=*/ 21, /* reset=*/ U8X8_PIN_NONE);  

void setup() {
  // put your setup code here, to run once:
  u8g2.enableUTF8Print();
  u8g1.enableUTF8Print();
  pinMode(19, OUTPUT);
  digitalWrite(19, HIGH);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  
  u8g1.begin();
  u8g2.begin();
  u8g1.setFont(u8g2_font_wqy16_t_gb2312b);
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  Serial.begin(57600);
  tft.init();

  spr.createSprite(x_limit, y_limit);  //attitude indicator
  spr2.createSprite(x_limit, y_limit); // 各种参数
  spr3.createSprite(70, 33);  //卫星个数
  spr5.createSprite(70, 33);  //电压
  spr6.createSprite(70, 33);  //速度
  spr4.createSprite(222, 40); //左下角 roll pitch

  tft.setRotation(1);
  screen_init();   


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

// task1code, 显示主显示屏信息
void Task1code( void * pvParameters ){
  // Serial.print("Task1 running on core ");
  // Serial.println(xPortGetCoreID());

  for(;;){
    get_mavlink_data();
    cal_att_cord();
    draw_new_attitude();
    draw_main_screen();
    spr.pushSprite(0, 35);  //attitude indicator       
    spr2.pushSprite(112,35); //各种参数
    spr4.pushSprite(0,200); //左下角 roll pitch
    spr3.pushSprite(40, 0); //卫星个数
    spr5.pushSprite(150, 0); //电压
    spr6.pushSprite(265, 0); //速度

    //计算主屏幕的fps3
    // now3 = millis();
    // frameCount3 ++;
    // if (now3 - Millis3rd >= 5000){
    //   fps3 = frameCount3/5;
    //   frameCount3 = 0;   
    //   Millis3rd = now3;        
    // }
      
  } 
}

//Task2code: 显示2、3屏幕信息
void Task2code( void * pvParameters ){
  // Serial.print("Task2 running on core ");
  // Serial.println(xPortGetCoreID());
  for(;;){
    //计算屏幕2的fps2,同时推送u8g2屏幕的信息
    now2 = millis();
    if (now2 - Millis2nd >= 1000){
    push_u8g2_fltmode();
    Millis2nd = now2;            
    }

    // 计算屏幕fps1
    now1 = millis();  
    frameCount1 ++;
    if (now1 - Millis1st >= 1000){
      fps1 = frameCount1;
      frameCount1 = 0;
      Millis1st = now1;             
    }   
    
  // 用上面1屏幕显示DC电流     
  push_u8g1_current();        
  }
}

void loop(void) {  

} // void loop
