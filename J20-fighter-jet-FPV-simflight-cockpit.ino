// ILI9341 library example
// (c) 2020 Pawel A. Hernik

/*
 ILI9341 240x320 2.2" tft pinout (header at the top, from left):

GND   -> GND
VCC   -> 3.3V

在Arduino\libraries\TFT_eSPI\User_Setup.h文件中修改引脚定义
// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP   ######
// For ESP32 Dev board (only tested with ILI9341 display)
// The hardware SPI can be mapped to any pins
#define TFT_MISO 13
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   10  // Chip select control pin
#define TFT_DC    7  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)
*/
#include <Arduino.h>
#define SCR_WD   320
#define SCR_HT   240
// #include "Free_Fonts.h" 
#include <SPI.h> //arduino自带，无需安装
#include <math.h> //arduino自带，无需安装
#include "pictures.h" // Image is stored here in an 8 bit array，已写好，无需安装
#include <Adafruit_GFX.h> 
#include "TFT_eSPI.h"
#include <PNGdec.h>
#include <U8g2lib.h>
#include <mavlink.h> //需手下载mavlink.zip文件，手动安装此库

// 双核运行所需handle，用于追踪执行情况
TaskHandle_t Task1;
TaskHandle_t Task2;

//显示图片所需变量
#define MAX_IMAGE_WDITH 320 // Adjust for your images
int16_t xpos;
int16_t ypos;
PNG png; // PNG decoder instance



TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);  // Declare Sprite object "spr" with pointer to "tft" object
TFT_eSprite spr2 = TFT_eSprite(&tft);  // Declare Sprite object "spr" with pointer to "tft" object
TFT_eSprite spr3 = TFT_eSprite(&tft);
TFT_eSprite spr4 = TFT_eSprite(&tft);
TFT_eSprite spr5 = TFT_eSprite(&tft);
TFT_eSprite spr6 = TFT_eSprite(&tft);

//定义下方副显示屏（2号屏）的虚拟对象，起名u8g2。
U8G2_SSD1306_72X40_ER_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 20, /* data=*/ 21, /* reset=*/ U8X8_PIN_NONE);  


//定义最上方副显示屏（3号屏）的虚拟对象，起名u8g3。
U8G2_SSD1306_96X16_ER_F_SW_I2C u8g3(U8G2_R0, /* clock=*/ 2, /* data=*/ 42, /* reset=*/ U8X8_PIN_NONE);  

//定义PNG文件所需变量
int16_t rc;  


#define BARWD 24
uint16_t colorBar[BARWD];

//mavlink definitions
mavlink_message_t msg; //定义一个mavlink 信息对象
mavlink_status_t status; // 定义一个mavlink status 对象
uint8_t msgReceived = false; 

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF
unsigned long color;

float roll = 0;
float pitch = 0.04;
float old_roll = 0;
float old_pitch = 0;
float yaw;

//#define MAVLINK_MSG_ID_SYS_STATUS 1
uint16_t voltage_battery; /*< [mV] Battery voltage, UINT16_MAX: Voltage not sent by autopilot*/
int16_t current_battery; /*< [cA] Battery current, -1: Current not sent by autopilot*/
int8_t battery_remaining; /*< [%] Battery energy remaining, -1: Battery remaining energy not sent by autopilot*/

// #define MAVLINK_MSG_ID_GPS_RAW_INT 24
// uint64_t time_usec; /*< [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.*/
// int32_t lat; /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
// int32_t lon; /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
// int32_t alt; /*< [mm] Altitude (MSL). Positive for up. Note that virtually all GPS modules provide the MSL altitude in addition to the WGS84 altitude.*/
// uint16_t eph; /*<  GPS HDOP horizontal dilution of position (unitless * 100). If unknown, set to: UINT16_MAX*/
// uint16_t epv; /*<  GPS VDOP vertical dilution of position (unitless * 100). If unknown, set to: UINT16_MAX*/
// uint16_t vel; /*< [cm/s] GPS ground speed. If unknown, set to: UINT16_MAX*/
uint16_t cog; /*< [cdeg] Course over ground (NOT heading, but direction of movement) in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX*/
// uint8_t fix_type; /*<  GPS fix type.*/
uint8_t satellites_visible; /*<  Number of satellites visible. If unknown, set to UINT8_MAX*/
// int32_t alt_ellipsoid; /*< [mm] Altitude (above WGS84, EGM96 ellipsoid). Positive for up.*/
// uint32_t h_acc; /*< [mm] Position uncertainty.*/
// uint32_t v_acc; /*< [mm] Altitude uncertainty.*/
// uint32_t vel_acc; /*< [mm] Speed uncertainty.*/
// uint32_t hdg_acc; /*< [degE5] Heading / track uncertainty*/
// uint16_t yaw; /*< [cdeg] Yaw in earth frame from north. Use 0 if this GPS does not provide yaw. Use UINT16_MAX if this GPS is configured to provide yaw and is currently unable to provide it. Use 36000 for north.*/

//#define MAVLINK_MSG_ID_GLOBAL_POSITION_INT 33
uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
// int32_t lat; /*< [degE7] Latitude, expressed*/
// int32_t lon; /*< [degE7] Longitude, expressed*/
// int32_t alt; /*< [mm] Altitude (MSL). Note that virtually all GPS modules provide both WGS84 and MSL.*/
int32_t relative_alt; /*< [mm] Altitude above ground*/
// int16_t vx; /*< [cm/s] Ground X Speed (Latitude, positive north)*/
// int16_t vy; /*< [cm/s] Ground Y Speed (Longitude, positive east)*/
// int16_t vz; /*< [cm/s] Ground Z Speed (Altitude, positive down)*/
uint16_t hdg; /*< [cdeg] Vehicle heading (yaw angle), 0.0..359.99 degrees. If unknown, set to: UINT16_MAX*/

//MAVLINK_MSG_ID_REQUEST_DATA_STREAM: //66
uint16_t req_message_rate;

// #define MAVLINK_MSG_ID_DATA_STREAM 67
uint16_t message_rate = 9; ///< The requested interval between two messages of this type
uint8_t stream_id = 9; ///< The ID of the requested data stream
uint8_t on_off; ///< 1 stream is enabled, 0 stream is stopped.


//#define MAVLINK_MSG_ID_VFR_HUD 74
float airspeed; /*< [m/s] Vehicle speed in form appropriate for vehicle type. For standard aircraft this is typically calibrated airspeed (CAS) or indicated airspeed (IAS) - either of which can be used by a pilot to estimate stall speed.*/
float groundspeed; /*< [m/s] Current ground speed.*/
float alt; /*< [m] Current altitude (MSL).*/
float climb; /*< [m/s] Current climb rate.*/
int16_t heading; /*< [deg] Current heading in compass units (0-360, 0=north).*/
uint16_t throttle; /*< [%] Current throttle setting (0 to 100).*/



//定义attitude indicator屏幕范围
float x_limit = 110; 
float y_limit = 160; 
//定义attitude indicator飞机中心x,y
float x_center = x_limit/2; 
float y_center = y_limit/2; 

float x0; //定义地平线中点x
float y_0; //定义地平线中点y，系统使用了y0，所以无法使用y0
float r0; //地平线中点距离飞机nose中心的距离

float alpha; // 地平线中点到屏幕中心的夹角
float beta; // 姿态线与屏幕x轴夹角
float cosa; //cos(alpha)
float sina; //sin(alpha)
float cosb; //cos(beta)
float sinb; //sin(beta)

//定义存储attitude数据的2维数组
int att_points[7][8];
//定义存储上一轮attitude数据的2维数组
int old_att_points[7][8];

float xa1, xa2, xa3, xa4, ya1, ya2, ya3, ya4; //0度地平线，长度跟其他pitch角度一样
float xb1, xb2, xb3, xb4, yb1, yb2, yb3, yb4; //定义一根长的0度地平线
float xb5, yb5, xb6, yb6, xb7, yb7, xb8, yb8; //定义用于绘制天空方框的四个点坐标
float old_xb1, old_xb2, old_xb3, old_xb4, old_yb1, old_yb2, old_yb3, old_yb4;
float xbs1, xbs2, xbs3, xbs4, ybs1, ybs2, ybs3, ybs4; //base level 水平姿态线，也就是屏幕中心level
float old_xbs1, old_xbs2, old_xbs3, old_xbs4, old_ybs1, old_ybs2, old_ybs3, old_ybs4;  //上一次base level 水平姿态线，也就是屏幕中心level
float xp1, xp2, xp3, xp4, yp1, yp2, yp3, yp4; // for循环里面画水平线用的坐标

//定义地平线长度 r1----r2  0  r3----r4 按这样的造型编号
float r1 = 30;
float r2 = 12;
float r3 = 12;
float r4 = 30;

//定义一根长的0度地平线
float l1 = 48;
float l2 = 8;
float l3 = 8;
float l4 = 48;

float l0 = 150; // 用于绘制地面天空的分界线

const int level_angle = 10; //定义各水平姿态线距离角度
const float level_pixel = 30; //各水平姿态线距离pix
const float pitch_to_pixel = level_pixel/radians(level_angle); //定义每10度地平线间的像素距离
float vx, vy; //level vector
float center_degree;
int base_vect; //baseline 距离0度地平线有几个姿态线档位
int old_base_vect;
String level_str;
int draw_level_angle;

//雷达绘制
float sinRadar;
float cosRadar;
float degreeRadar;

// float main_dis = 28;
float theta;
char level_char[10];
unsigned long Millis1st = 0;
unsigned long Millis2nd = 0;
unsigned long Millis3rd = 0;
unsigned long Millis4th = 0;
unsigned long now1 = 0;
unsigned long now2 = 0;
unsigned long now3 = 0;
unsigned long now4 = 0;
unsigned long frameCount1 = 0;
unsigned long frameCount2 = 0;
unsigned long frameCount3 = 0;
unsigned long frameCount4 = 0;
unsigned long fps1 = 0;
unsigned long fps2 = 0;
unsigned long fps3 = 0;



void setup() {
  // put your setup code here, to run once:
  u8g2.enableUTF8Print();
  u8g3.enableUTF8Print();
  pinMode(19, OUTPUT);
  digitalWrite(19, HIGH);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);

  u8g2.begin();
  u8g3.begin();
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
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    get_mavlink_data();
    cal_att_cord();
    draw_new_attitude();
    draw_hud();
    spr.pushSprite(0, 35);  //attitude indicator        

    now1 = millis();  

    if (now1 - Millis4th >= 500){
      spr2.pushSprite(112,35); //各种参数
      spr4.pushSprite(0,200); //左下角 roll pitch
      spr3.pushSprite(40, 0); //卫星个数
      spr5.pushSprite(150, 0); //电压
      spr6.pushSprite(265, 0); //速度
      Millis4th = now1;            
    }    

    //计算主屏幕fps1
    frameCount1 ++;
    if (now1 - Millis1st >= 5000){
      fps1 = frameCount1/5;
      frameCount1 = 0;
      Millis1st = now1;             
    }      
  } 
}

//Task2code: 显示2、3屏幕信息
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    
    // u8g2 72X40
      //画出雷达
      u8g2.clearBuffer();
      u8g2.drawCircle(20,20,19, U8G2_DRAW_ALL);
      u8g2.drawLine(20, 20, 19*cos(degreeRadar*71/4068)+20, 19*sin(degreeRadar*71/4068)+20);
      // u8g2.drawLine(20, 20, 19*cos((degreeRadar+4)*71/4068)+20, 19*sin((degreeRadar+4)*71/4068)+20); 
      u8g2.drawLine(20, 20, 19*cos((degreeRadar+8)*71/4068)+20, 19*sin((degreeRadar+8)*71/4068)+20); 
      // u8g2.drawLine(20, 20, 19*cos((degreeRadar+12)*71/4068)+20, 19*sin((degreeRadar+12)*71/4068)+20);   
      u8g2.drawLine(20, 20, 19*cos((degreeRadar+16)*71/4068)+20, 19*sin((degreeRadar+16)*71/4068)+20); 
      // u8g2.drawLine(20, 20, 19*cos((degreeRadar+20)*71/4068)+20, 19*sin((degreeRadar+20)*71/4068)+20); 
      u8g2.drawLine(20, 20, 19*cos((degreeRadar+24)*71/4068)+20, 19*sin((degreeRadar+24)*71/4068)+20);  
      u8g2.setCursor(50,14);
      u8g2.print("扫");     
      u8g2.setCursor(50,38);
      u8g2.print("描");       
      u8g2.sendBuffer();
      degreeRadar = degreeRadar + 20;
      if (degreeRadar > 360) {
        degreeRadar = degreeRadar - 360;        
      }        
    // now2 = millis();
    // if (now2 - Millis2nd >= 100){
      
      // Millis2nd = now2; 
            
      // u8g2.clearBuffer();
      // u8g2.setCursor(0,14);
      // u8g2.print("fps3: ");
      // u8g2.setCursor(40,14);
      // u8g2.print(fps3);      
      // u8g2.setCursor(0,38);  
      // u8g2.print("fps1: ");
      // u8g2.setCursor(40,38);
      // u8g2.print(fps1);      
      // u8g2.sendBuffer();
      
    // }
    
    now3 = millis();
    u8g3.clearBuffer();
    u8g3.setFont(u8g2_font_wqy16_t_gb2312b);
    u8g3.setCursor(20, 14);   
    u8g3.print("DC: ");
    u8g3.print(double(current_battery)/100, 2);
    u8g3.sendBuffer();
    
    //计算屏幕3的fps3
    frameCount3 ++;
    if (now3 - Millis3rd >= 5000){
      fps3 = frameCount3/5;
      frameCount3 = 0;   
      Millis3rd = now3;        
    }
    
    
        
  }
}

void loop(void) {  

} // void loop
