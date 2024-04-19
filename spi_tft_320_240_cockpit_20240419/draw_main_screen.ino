void draw_main_screen(){
  // spr2.setFreeFont(FSS9);
  spr2.fillSprite(BLACK);  
  spr2.drawRect(0,0,x_limit,y_limit,YELLOW);
  spr2.setTextColor(YELLOW, BLACK);
  spr2.setTextFont(2); 
  int RH = 20; // row hight
  int CW = 50; // collumn width
  

  //表格起始位置
  int x_spr2 = 10;
  int y_spr2 = 2;

  //开始写入数据
  spr2.setCursor(x_spr2, y_spr2); spr2.print("TIME");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(time_boot_ms/1000/60);spr2.print(":");spr2.print(time_boot_ms/1000%60);
  y_spr2 = y_spr2 + RH;
  spr2.setCursor(x_spr2, y_spr2); spr2.print("A/S");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(airspeed);   
  y_spr2 = y_spr2 + RH; 
  spr2.setCursor(x_spr2, y_spr2); spr2.print("HEAD");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(heading); 
  y_spr2 = y_spr2 + RH;
  spr2.setCursor(x_spr2, y_spr2); spr2.print("COG");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(cog);
  y_spr2 = y_spr2 + RH; 
  spr2.setCursor(x_spr2, y_spr2); spr2.print("CLB");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(climb);   
  y_spr2 = y_spr2 + RH;
  spr2.setCursor(x_spr2, y_spr2); spr2.print("BATR");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(battery_remaining);
  // y_spr2 = y_spr2 + RH;
  // spr2.setCursor(x_spr2, y_spr2); spr2.print("CURR");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(double(current_battery)/100, 2);
  y_spr2 = y_spr2 + RH;
  spr2.setCursor(x_spr2, y_spr2); spr2.print("RALT");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(double(relative_alt)/1000, 2);
  y_spr2 = y_spr2 + RH;
  spr2.setCursor(x_spr2, y_spr2); spr2.print("Yaw");spr2.setCursor(x_spr2+CW, y_spr2); spr2.print(yaw);

  spr3.fillSprite(BLACK);
  spr3.setTextColor(YELLOW, BLACK);
  spr3.setTextFont(4);     
  spr3.setCursor(2, 5); spr3.print(satellites_visible);

  spr5.fillSprite(BLACK);
  spr5.setTextColor(YELLOW, BLACK);
  spr5.setTextFont(4);   
  spr5.setCursor(2, 5); spr5.print(double(voltage_battery)/1000,2);
  
  spr6.fillSprite(BLACK);
  spr6.setTextColor(YELLOW, BLACK);
  spr6.setTextFont(4);  
  spr6.setCursor(2, 5); spr6.print(groundspeed*3.6,1);

  spr4.fillSprite(TFT_BLACK);
  spr4.drawRect(0,0,222,40,YELLOW);
  spr4.setTextColor(YELLOW, BLACK);
  spr4.setTextFont(2);   
  spr4.setCursor(5, 2); spr4.print("Pitch");spr4.setCursor(42, 2); spr4.print(pitch/PI*180, 2);
  spr4.setCursor(5, 20); spr4.print("Roll");spr4.setCursor(42, 20); spr4.print(roll/PI*180, 2);
  
  spr4.setCursor(120, 2); spr4.print("THROTTLE "); spr4.print(throttle);
  spr4.drawRect(115, 20,100,15,YELLOW);
  spr4.fillRect(115, 20, throttle, 15,YELLOW);
  

    


  
}