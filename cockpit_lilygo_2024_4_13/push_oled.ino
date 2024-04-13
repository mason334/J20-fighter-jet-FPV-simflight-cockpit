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
  brightness_new_main = (chan6_raw-1000)*255/1000; //only the integral part is stored and the fractional part of the number is lost
  if (abs(brightness_new_main - brightness_old_main) > 20){
    lcd_brightness(brightness_new_main);
    brightness_old_main = brightness_new_main;
  }
}

void adjust_brightness_small(){
  brightness_new = (chan6_raw-1000)*255/1000; //only the integral part is stored and the fractional part of the number is lost
  if (abs(brightness_new - brightness_old) > 8){
    u8g1.setContrast(brightness_new);
    u8g2.setContrast(brightness_new/4);
    brightness_old = brightness_new;
  }
}