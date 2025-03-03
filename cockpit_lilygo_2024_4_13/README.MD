# Ardupilot参数调整以优化显示延迟

## 1. MAVLink数据流参数调整

### 关键数据流频率设置
```
SR1_EXT_STAT = 10
SR1_EXTRA1 = 10
SR1_EXTRA2 = 10
SR1_EXTRA3 = 10
SR1_POSITION = 10
SR1_RAW_CTRL = 0
SR1_RAW_SENS = 2
SR1_RC_CHAN = 2
```
- 将关键数据流设置为10Hz以获得更流畅的显示
- 非关键数据流可以设置较低频率以减少带宽占用

### 串口配置
```
SERIAL1_BAUD = 115200    # 提高波特率
SERIAL1_OPTIONS = 0      # 禁用流控
SERIAL1_PROTOCOL = 1     # 使用MAVLink v1协议
```
# 0.69寸96x16显示屏接线如下  
显示屏引脚 &nbsp; &nbsp; &nbsp; ESP32引脚  
SCL/SCK &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 1  
SDA &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 2  
VCC &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 3V3  
GND &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; GND  

# 0.42寸72x40显示屏接线如下  
显示屏引脚 &nbsp; &nbsp; &nbsp; ESP32引脚  
SCL/SCK &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;41  
SDA &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 40  
VCC &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 3V3  
GND &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; GND