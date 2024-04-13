//hud数据 128x128
void push_u8g3()
{
  u8g3.clearBuffer();
  draw_hud_attitude();
  if (rangefinder_distance < 30){
    u8g3.setCursor(37, 40);
    u8g3.print("超低空");  
    u8g3.setCursor(40, 90);
    u8g3.setDrawColor(0);
    u8g3.drawBox(35,70,60,20);
    u8g3.setDrawColor(1);
    u8g3.print(rangefinder_distance, 1);  
    u8g3.print(" 米");  
  }
  u8g3.sendBuffer();
}

void adjust_brightness(){
  brightness_new = (chan6_raw-1000)*255/1000; //only the integral part is stored and the fractional part of the number is lost
  if (abs(brightness_new - brightness_old) > 20){
    u8g3.setContrast(brightness_new);
    brightness_old = brightness_new;
  }
}