//定义attitude indicator屏幕范围
float scale = 1.5;
float x_limit = 110 * scale; //定义姿态仪画布大小
float y_limit = 160 * scale; //定义姿态仪画布大小

float hud_scale_x = 0.78; //
float hud_scale_y = 0.53;
int hud_x_limit = 128; //定义hud姿态仪画布大小
int hud_y_limit = 128; //定义hud姿态仪画布大小

//定义main screen attitude indicator中心坐标
float x_center = x_limit/2; 
float y_center = y_limit/2; 

//定义hud attitude indicator中心坐标
float x_center_h; 
float y_center_h; 

float x0; //定义飞机中点x
float y_0; //定义飞机中点y，系统使用了y0，所以无法使用y0
float r0; //姿态仪中点距离飞机nose中心的距离

float alpha; // 姿态仪法线与地平线的夹角
float beta; // 姿态线与屏幕x轴夹角
float cosa; //cos(alpha)
float sina; //sin(alpha)
float cosb; //cos(beta)
float sinb; //sin(beta)
float theta;
char level_char[10];

float roll = 0;
float pitch = 0.04;
float old_roll = 0;
float old_pitch = 0;
float yaw;

//定义存储attitude数据的2维数组
int att_points[7][8];

//定义存储上一轮attitude数据的2维数组
int old_att_points[7][8];

//定义hud attitude数据的2维数组
int hud_att_points[7][8];

float xa1, xa2, xa3, xa4, ya1, ya2, ya3, ya4; //0度地平线，长度跟其他pitch角度一样，用于计算其他姿态线坐标
float xb1, xb2, xb3, xb4, yb1, yb2, yb3, yb4; //定义一根长的0度地平线
float xb1_h, xb2_h, xb3_h, xb4_h, yb1_h, yb2_h, yb3_h, yb4_h; //为hud定义一根长的0度地平线
float xb5, yb5, xb6, yb6, xb7, yb7, xb8, yb8; //定义用于绘制天空方框的四个点坐标
float old_xb1, old_xb2, old_xb3, old_xb4, old_yb1, old_yb2, old_yb3, old_yb4;
float xbs1, xbs2, xbs3, xbs4, ybs1, ybs2, ybs3, ybs4; //base level 姿态仪中心level
float old_xbs1, old_xbs2, old_xbs3, old_xbs4, old_ybs1, old_ybs2, old_ybs3, old_ybs4;  //上一次base level 水平姿态线，也就是屏幕中心level
float xp1, xp2, xp3, xp4, yp1, yp2, yp3, yp4; // for循环里面画水平线用的坐标

//定义地平线长度 r1----r2  0  r3----r4 按这样的造型编号，数字是从中心出发的像素
float r1 = 30 * scale;
float r2 = 15 * scale;
float r3 = 15 * scale;
float r4 = 30 * scale;

//定义一根长的0度地平线
float l1 = 48 * scale;
float l2 = 8 * scale;
float l3 = 8 * scale;
float l4 = 48 * scale;

float l0 = 150 * scale; // 用于绘制地面天空的分界线
const float level_pixel = 30 * scale; //各水平姿态线距离pix

const int level_angle = 10; //定义各水平姿态线距离角度

const float pitch_to_pixel = level_pixel/radians(level_angle); //定义每10度地平线间的像素距离
float vx, vy; //level vector，相邻姿态线中点连线形成的矢量
float center_degree; //pitch的角度值，飞控给的pitch值是幅度值
int base_vect; // 离姿态仪中心最近的姿态线编号 base
int old_base_vect;
String level_str;
int draw_level_angle; //需要画出来的那条水平姿态线

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
#define GRAY     0x2A0A
unsigned long color;
uint8_t brightness_new_main; //lilygo amoled 最亮值255，对应pwm 1900 最暗值0，对应pwm 1100. 
uint8_t brightness_old_main;

uint8_t brightness_new; //lilygo amoled 最亮值255，对应pwm 1900 最暗值0，对应pwm 1100. 
uint8_t brightness_old;

//pngdecorder 用的变量和参数
#define MAX_IMAGE_WDITH 320 // Adjust for your images
int16_t rc;
int16_t xpos;
int16_t ypos;

// #define MAVLINK_MSG_ID_HEARTBEAT 0
uint8_t base_mode;
uint32_t custom_mode;
uint32_t flight_mode;
String flight_mode_str;
uint8_t system_status;
String system_status_str;
//#define MAVLINK_MSG_ID_AVAILABLE_MODES 435
uint8_t mode_index; /*<  The current mode index within number_modes, indexed from 1.*/

//#define MAVLINK_MSG_ID_SYS_STATUS 1
uint16_t voltage_battery = 19200; /*< [mV] Battery voltage, UINT16_MAX: Voltage not sent by autopilot*/
int16_t current_battery; /*< [cA] Battery current, -1: Current not sent by autopilot*/
int8_t battery_remaining; /*< [%] Battery energy remaining, -1: Battery remaining energy not sent by autopilot*/

//#define MAVLINK_MSG_ID_BATTERY_STATUS 147
int32_t current_consumed; /*< [mAh] Consumed charge, -1: autopilot does not provide consumption estimate*/

// #define MAVLINK_MSG_ID_GPS_RAW_INT 24
uint16_t cog; /*< [cdeg] Course over ground (NOT heading, but direction of movement) in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX*/
uint8_t fix_type; /*<  GPS fix type.*/
uint8_t satellites_visible; /*<  Number of satellites visible. If unknown, set to UINT8_MAX*/

//#define MAVLINK_MSG_ID_DISTANCE_SENSOR 132
float current_distance; /*< [cm] Current distance reading*/
float rangefinder_distance;

//#define MAVLINK_MSG_ID_GLOBAL_POSITION_INT 33
uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
int32_t relative_alt; /*< [mm] Altitude above ground*/
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

// #define MAVLINK_MSG_ID_RC_CHANNELS_RAW 35
 uint16_t chan1_raw; ///< RC channel 1 value, in microseconds
 uint16_t chan2_raw; ///< RC channel 2 value, in microseconds
 uint16_t chan3_raw; ///< RC channel 3 value, in microseconds
 uint16_t chan4_raw; ///< RC channel 4 value, in microseconds
 uint16_t chan5_raw; ///< RC channel 5 value, in microseconds
 uint16_t chan6_raw; ///< RC channel 6 value, in microseconds
 uint16_t chan7_raw; ///< RC channel 7 value, in microseconds
 uint16_t chan8_raw; ///< RC channel 8 value, in microseconds
 uint8_t port; ///< Servo output port (set of 8 outputs = 1 port). Most MAVs will just use one, but this allows to encode more than 8 servos.

// MESSAGE RADIO_STATUS PACKING 109
 uint8_t rssi; ///< Receive signal strength indicator, 0: 0%, 255: 100%

// 定义time string
String time_str;

unsigned long Millis0 = 0;
unsigned long Millis1st = 0;
unsigned long Millis2nd = 0;
unsigned long Millis3rd = 0;
unsigned long Millis4th = 0;
unsigned long now0 = 0;
unsigned long now1 = 0;
unsigned long now2 = 0;
unsigned long now3 = 0;
unsigned long now4 = 0;
unsigned long frameCount0 = 0;
unsigned long frameCount1 = 0;
unsigned long frameCount2 = 0;
unsigned long frameCount3 = 0;
unsigned long frameCount4 = 0;
unsigned long fps0 = 0;
unsigned long fps1 = 0;
unsigned long fps2 = 0;
unsigned long fps3 = 0;
volatile bool mavlink_data_ready = false;