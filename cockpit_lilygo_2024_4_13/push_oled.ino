/*
void push_main_screen()
{

  
  get_mavlink_data();
  cal_att_cord();
  draw_new_attitude();
  lcd_PushColors(0, 0, 165, 240, (uint16_t*)spr.getPointer());

  now0 = millis();
    if (now0 - Millis0 >= 500){
      draw_meters();
      draw_meters_2();
      lcd_PushColors(166+4, 0, 80, 240, (uint16_t*)spr_meters.getPointer());
      lcd_PushColors(536-80, 0, 80, 240, (uint16_t*)spr_meters_2.getPointer());
    }      

    if (now0 - Millis0 >= 500){
      draw_mid();
      lcd_PushColors(166+4+80, 0, 200, 240, (uint16_t*)spr_mid.getPointer());  
    }      
}
*/

void push_main_screen() {
  static uint32_t last_meters_update = 0;
  const uint32_t METERS_UPDATE_INTERVAL = 500; // 500ms更新一次仪表
  get_mavlink_data();
  // 更新姿态显示
  cal_att_cord();
  draw_new_attitude();
  lcd_PushColors(0, 0, 165, 240, (uint16_t*)spr.getPointer());

  // 更新仪表和中间显示区域
  uint32_t now = millis();
  if (now - last_meters_update >= METERS_UPDATE_INTERVAL) {
    draw_meters();
    draw_meters_2();
    lcd_PushColors(166+4, 0, 80, 240, (uint16_t*)spr_meters.getPointer());
    lcd_PushColors(536-80, 0, 80, 240, (uint16_t*)spr_meters_2.getPointer());
    
    draw_mid();
    lcd_PushColors(166+4+80, 0, 200, 240, (uint16_t*)spr_mid.getPointer());
    
    last_meters_update = now;
  }
}



// 上方小屏数据 96X16
void push_u8g1()
{
  u8g1.clearBuffer();
  u8g1.setFont(u8g2_font_wqy16_t_gb2312b);
  u8g1.setCursor(10, 14);   
  u8g1.print("动力: ");
  u8g1.print(double(current_battery)/100, 1);
  u8g1.sendBuffer();
}

//下方小屏数据 72X40
void push_u8g2()
{
  u8g2.clearBuffer();
  u8g2.setCursor(0, 16); 
  u8g2.print("飞行模式:");
  u8g2.setCursor(0, 36);
  u8g2.print(flight_mode_str);
  u8g2.sendBuffer();
}


void adjust_brightness_main(){
  // 将遥控器通道7的值(1000-2000)映射到亮度值(0-255)
  brightness_new_main = (chan7_raw-1000)*255/1000; 
  
  // 只有当亮度变化超过20才更新,避免频繁调整
  if (abs(brightness_new_main - brightness_old_main) > 20){
    lcd_brightness(brightness_new_main);
    brightness_old_main = brightness_new_main;
  }
}

void adjust_brightness_small(){
  // 同样映射遥控器通道7的值到亮度值
  brightness_new = (chan7_raw-1000)*255/1000;
  
  // 亮度变化超过8时才更新
  if (abs(brightness_new - brightness_old) > 8){
    u8g1.setContrast(brightness_new);
    // 第二个OLED亮度值除以4(可能是因为其亮度范围不同)
    u8g2.setContrast(brightness_new/4);
    brightness_old = brightness_new;
  }
}