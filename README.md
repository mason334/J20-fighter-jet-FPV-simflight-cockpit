# J20-fighter-jet-FPV-simflight-cockpit
## J20战机模拟座舱 Chengdu J20 fighter jet FPV simflight cockpit  
由于各种原因，最终只能有少部分人人成为飞行员，翱翔在蓝天。但是，我们依然向往飞行！  
多亏半导体和无线电技术的高速发展，已经让FPV飞行成为可能。  
现在，我们把飞行体验往前再推进一步。  
采用这套模拟座舱系统，通过3D打印和数字图传系统，你可以坐进模拟座舱，体验身临其境的战斗机驾驶乐趣。  
这套J20模拟座舱系统由硬件和软件组成。  


硬件由4部分组成  
- 机舱：包含显示器、散热风扇、DJI O3天空端等安装座。
- 舱盖：包括舱盖框架和风挡文件。
- 显示器：1块0.69寸OLDE显示器， 1块0.42寸OLED显示器，和1块2.2寸主tft lcd显示器或者1.9寸amoled主显示器。
- 显示器控制单片机：ESP32-S3  

软件部分是一套用arduino编程语言编写的ESP32-S3控制程序。ESP32-S3通过UART串口与飞控通信，采用mavlink协议。  
通过mavlink协议读取的数据，ESP32-S3驱动3块显示器显示我们想要的信息，包括姿态仪、图案、各种飞行数据。  
**这样就给一个FPV座舱注入了灵魂：实时、动态的飞行数据。**  
你甚至可以不看图传眼镜里面的OSD数据，直接通过座舱的显示器实现仪表飞行。  


## 准备工作
使用这套J20模拟座舱前，你需要具备基础的航模飞行经验，并且具备以下FPV基础硬件条件：  
- **一架天捷力 新小胖 载机**
- 一套航模飞机遥控系统  
- 一套DJI O3数字图传系统（座舱模型是根据O3数字图传系统设计的，如果采用其他图传系统，需要自行修改座舱模型）  
- 能够定义串口通信协议的飞控：例如支持ardupilot固件或者iNav固件的飞控。用于座舱和飞控的数据通信。  
- DJI FPV飞行眼镜  
如果你不具备上述条件，说明你还不适合直接开展仿真模拟FPV飞行。请先学习航模目视飞行，并学会基础的FPV知识再回来。
<img src="https://github.com/mason334/images/blob/main/IMG_1116.JPG" alt="drawing" width="600"/>


完成以上准备工作后，你离仿真模拟飞行的距离只差几步了，而且总共花费不到300元人民币（TFT版）。  
## 第零步，选择你喜欢的座舱版本
- 目前开发了两个版本的座舱。
- 一个是采用2.2寸tft显示屏的座舱，主显示屏成本较低（约35元）。使用文件夹“spi_tft_320_240_cockpit_20240419”里面的代码驱动2.2寸 tft显示屏。
- 另外一个版本是采用amoled的显示屏，主显示屏成本高（约190元），结果是比例更协调，亮度更高，颜色更鲜艳。使用文件夹“cockpit_lilygo_2024_4_13”里面的代码驱动lilygo amoled显示屏。这个版本的座舱还配备了光学HUD，需要一块单独的esp32单片机来驱动。使用文件夹“oled_hud_attitude_indicator_2024_4_9”里的代码来驱动这个光学hud。
- 相关视频效果见up主B站相关视频，传送连接https://space.bilibili.com/1096820983


## 第一步 打印座舱和舱盖。按照风挡文件，裁剪孰料片，制作风挡  
<img src="https://github.com/mason334/images/blob/main/IMG_0859.JPG" alt="drawing" width="600"/>
由于TFT LCD屏幕在阳光下亮度不够，直接在阳光下无法看清屏幕。所以风挡采用遮光塑料片，用于阳光下飞行使用。也可采用透明塑料片制作，非强光下飞行使用。

## 第二步 购买电子设备  
- ESP32-s3单片机（源地工作室，esp32-S3 N16R8)
- 信利光电 0.69寸 96x16 OLED SSD1306
- 信利光电0.42 72x40 OLED SSD1306
- 信泰微电子 2.2寸 ILI9341 SPI TFT LCD （适配SPI TFT 版座舱）
- Lilygo T-display s3 1.9寸amoled 显示屏 （适配Lilygo AMOLED版座舱）
- 光学HUD使用的显示屏采用1.5寸Futaba ELW501AAR 128*128 OLED显示屏（日本进口灰阶oled屏，类似的SSD1327芯片驱动的128X128OLED也可以）
- 盈讯 3510 液压轴承 散热风扇

## 第三步 焊接  
根据控制程序要求，焊接3块屏幕和ESP32单片机的接线。焊接ESP32单片机与飞控通信的排线。
# Lilygo T-display s3 amoled 显示屏无需焊接，屏幕和esp32单片机已经连接好

# 2.2寸显示屏接线如下  
显示屏引脚 &nbsp; &nbsp; ESP32引脚  
MISO &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;13  
MOSI &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;11  
SCLK &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 12  
CS &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 10  // Chip select control pin  
DC &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 7  // Data Command control pin  
RST &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 4  // Reset pin (could connect to RST pin)  
LED &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 3V3  
VCC &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 3V3   
GND &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; GND  

# 0.69寸96x16显示屏接线如下  
显示屏引脚 &nbsp; &nbsp; &nbsp; ESP32引脚  
SCL/SCK &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 1  
SDA &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 2  
VCC &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 3V3  
GND &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; GND  
# 0.42寸72x40显示屏接线如下  
显示屏引脚 &nbsp; &nbsp; &nbsp; ESP32引脚  
SCL/SCK &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;20  
SDA &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 21  
VCC &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 3V3  
GND &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; GND

# 飞控串口通讯接线
ESP32引脚 &nbsp; &nbsp; &nbsp; 飞控串口引脚  
RX &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; TX  
GND &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;GND  

## 在T-Display-S3 AMOLED开发板上对应的引脚是：
TX &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; GPIO43  
RX &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; GPIO44  

连接方式：

飞控的TX连接到开发板的RX(GPIO44)

飞控的GND连接到开发板的GND

波特率：115200（觉得高的可以代码中修改Serial.begin(115200);）


注意：如果只是接收数据，只需要连接这两根线即可


<img src="https://github.com/mason334/images/blob/main/IMG_0875.JPG" width="600"/>

## 第四步 上传代码，点亮屏幕  
将代码下载后，放到arduino项目目录下，文件夹名称与主程序文件名称一致（J20-fighter-jet-FPV-simflight-cockpit）  
安装ESP32开发板：ESP32S3 Dev Module  
根据主程序代码中include部分要求，安装所需的库文件。
Arduino已经有匹配的MAVlink库了，可以直接在arduino ide中下载安装，不再需要手动下载导入。
通过机载5V电源，给ESP32单片机供电，点亮屏幕。 **尽量不要用飞控给ESP32供电，避免飞控电流过载。**  
将代码上传到ESP32单片机。注意esp32-S3 N16R8开发板有两个type c接口，上传代码时只能用com这个口（type c接口背面有标注）  
将串口接上飞控，飞控对应的串口选择**mavlink 1**协议，获得屏幕数据。    
- SPI TFT LCD 版座舱
<img src="https://github.com/mason334/images/blob/main/IMG_1055.JPG" alt="drawing" width="600"/>
- Lilygo AMOLED版座舱
<img src="https://github.com/mason334/images/blob/main/IMG_3536.JPG" alt="drawing" width="600"/>


## 第五步 安装其他设备  
将天空端、散热风扇安装好，然后座舱盖固定到机舱上，完成安装
<img src="https://github.com/mason334/images/blob/main/IMG_0936.JPG" alt="drawing" width="600"/>

<img src="https://github.com/mason334/images/blob/main/IMG_0922.JPG" alt="drawing" width="600"/>

<img src="https://github.com/mason334/images/blob/main/IMG_0932.JPG" alt="drawing" width="600"/>

<img src="https://github.com/mason334/images/blob/main/IMG_0934.JPG" alt="drawing" width="600"/>


