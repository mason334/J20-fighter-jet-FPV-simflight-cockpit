void draw_meters(){
  // spr_meters.drawRect(2,0,275,240,GREEN);
  spr_meters.setTextColor(WHITE, BLACK);
  int x_start = 0;
  int y_start = 0;
    for (int j = 0; j < 3; j++){
      spr_meters.fillSmoothRoundRect(x_start,j*81+y_start, 78, 78, 6, GRAY, TFT_BLACK);
    }  
  spr_meters.loadFont(Final_Frontier_28);
  spr_meters.setCursor(x_start+10, 0*81+y_start+30); spr_meters.print(airspeed*3.6, 1); //空速换算成km/h
  spr_meters.drawSmoothArc(x_start+38, 0*81+y_start+40, 36, 33, 60, 300, BLACK, BLACK, true);
  spr_meters.drawSmoothArc(x_start+38, 0*81+y_start+40, 36, 33, 60, int32_t(60+airspeed*240/150+1), YELLOW, BLACK, true); //预计速度最高不超过150km/h
  spr_meters.setCursor(x_start+10, 1*81+y_start+30); spr_meters.print(groundspeed*3.6, 1); //地速换算成km/h
  spr_meters.drawSmoothArc(x_start+38, 1*81+y_start+40, 36, 33, 60, 300, BLACK, BLACK, true);
  spr_meters.drawSmoothArc(x_start+38, 1*81+y_start+40, 36, 33, 60, int32_t(60+groundspeed*240/150+1), YELLOW, BLACK, true); //预计速度最高不超过150km/h

  if (alt > 100) {alt = 100;}
  spr_meters.setCursor(x_start+10, 2*81+y_start+30); spr_meters.print(alt); 
  spr_meters.drawSmoothArc(x_start+38, 2*81+y_start+40, 36, 33, 60, 300, BLACK, BLACK, true);
  spr_meters.drawSmoothArc(x_start+38, 2*81+y_start+40, 36, 33, 60, int32_t(60+alt*240/100+1), YELLOW, BLACK, true); //高度显示最多100m

  spr_meters.loadFont(cn_ht_26);     
  spr_meters.drawString("空速",x_start+12, 0*81+y_start+55); //从左上角开始计算坐标
  spr_meters.drawString("地速",x_start+12, 1*81+y_start+55); //从左上角开始计算坐标
  spr_meters.drawString("高度",x_start+12, 2*81+y_start+55); //从左上角开始计算坐标
  spr_meters.unloadFont();
}

void draw_meters_2(){
  // spr_meters.drawRect(2,0,275,240,GREEN);
  spr_meters_2.setTextColor(WHITE, BLACK);
  int x_start = 0;
  int y_start = 0;
    for (int j = 0; j < 3; j++){
      spr_meters_2.fillSmoothRoundRect(x_start,j*81+y_start, 78, 78, 6, GRAY, TFT_BLACK);
    }
  spr_meters_2.loadFont(Final_Frontier_28);
  spr_meters_2.setCursor(x_start+10, 0*81+y_start+30); spr_meters_2.print(double(current_battery)/100, 1); 
  spr_meters_2.drawSmoothArc(x_start+38, 0*81+y_start+40, 36, 33, 60, 300, BLACK, BLACK, true);
  spr_meters_2.drawSmoothArc(x_start+38, 0*81+y_start+40, 36, 33, 60, int32_t(60+current_battery*240/5000+1), YELLOW, BLACK, true); //最高电流按5000cA预估

  if (voltage_battery < 19200) {voltage_battery = 19200;}
  spr_meters_2.setCursor(x_start+10, 1*81+y_start+30); spr_meters_2.print(double(voltage_battery)/6000, 1); //6s电池，计算每节电池电压
  spr_meters_2.drawSmoothArc(x_start+38, 1*81+y_start+40, 36, 33, 60, 300, BLACK, BLACK, true);
  spr_meters_2.drawSmoothArc(x_start+38, 1*81+y_start+40, 36, 33, 60, int32_t(60+(voltage_battery-19200)*240/6000+1), YELLOW, BLACK, true);//最高电压按6s电池25.2V预估

  spr_meters_2.setCursor(x_start+10, 2*81+y_start+30); spr_meters_2.print(brightness_new*100/255); 
  spr_meters_2.drawSmoothArc(x_start+38, 2*81+y_start+40, 36, 33, 60, 300, BLACK, BLACK, true);
  spr_meters_2.drawSmoothArc(x_start+38, 2*81+y_start+40, 36, 33, 60, int32_t(60+brightness_new*240/255+1), YELLOW, BLACK, true); //亮度信号最高255

  spr_meters_2.loadFont(cn_ht_26);     
  spr_meters_2.drawString("电流",x_start+12, 0*81+y_start+55); //从左上角开始计算坐标  
  spr_meters_2.drawString("电压",x_start+12, 1*81+y_start+55); //从左上角开始计算坐标  
  spr_meters_2.drawString("亮度",x_start+12, 2*81+y_start+55); //从左上角开始计算坐标  
  spr_meters_2.unloadFont();  
}

void draw_mid(){
  spr_mid.fillSprite(BLACK); 
  // spr_mid.drawRect(0, 0, 200, 240,GREEN);
  spr_mid.setSwapBytes(true); //纠正pushimage颜色不对的问题
  spr_mid.pushImage(45, 0, 109, 182, j20_109_182); 
  spr_mid.pushImage(5, 0, 45, 43, salt_45_43); 

  spr_mid.loadFont(Final_Frontier_28);
  spr_mid.fillRect(55, 10, 35, 30, BLACK);
  spr_mid.setCursor(55, 10); spr_mid.print(satellites_visible);
  // spr_mid.fillRect(130, 10, 70, 30, BLACK);
  time_str = String(time_boot_ms/1000/60)+":"+String(time_boot_ms/1000%60);
  spr_mid.drawString(time_str, 130, 10);
  spr_mid.unloadFont();
//current_consumed 电量状态条，4000mah为100%
  spr_mid.drawRect(170, 55, 20, 120,GREEN);
  spr_mid.fillRect(170, 55+current_consumed*120/4000, 20, 120-current_consumed*120/4000, GREEN);
//油门状态条
  spr_mid.drawRect(13, 55, 20, 120, GREEN);
  spr_mid.fillRect(13, 55+120-throttle*120/100, 20, throttle*120/100, GREEN);


  spr_mid.setTextColor(WHITE, BLACK);
  spr_mid.loadFont(cn_ht_26);
  spr_mid.drawString("油",10,185); //从左上角开始计算坐标
  spr_mid.drawString("门",10,215); //从左上角开始计算坐标
  spr_mid.drawString("电",165,185); //从左上角开始计算坐标
  spr_mid.drawString("量",165,215); //从左上角开始计算坐标

  spr_mid.fillSmoothRoundRect(45,190, 109, 50, 6, BLUE, TFT_BLACK);
  spr_mid.drawString("系统状态", 50, 195); //从左上角开始计算坐标
  spr_mid.setCursor(50, 220); 
  spr_mid.print(system_status_str);
  // spr_mid.setCursor(50, 220); spr_mid.print("rssi:");spr_mid.print(rssi)
  // spr_mid.print("FPS:");spr_mid.print(fps0);
  spr_mid.unloadFont();
}