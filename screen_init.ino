void screen_init(){
//在HUD屏幕以及下方中控台显示欢迎语句
  //U8G2_SSD1306_72X40_ER_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 20, /* data=*/ 21, /* reset=*/ U8X8_PIN_NONE);  
  //U8G2_SSD1306_96X16_ER_F_SW_I2C u8g3(U8G2_R0, /* clock=*/ 2, /* data=*/ 42, /* reset=*/ U8X8_PIN_NONE);  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  u8g2.setCursor(0,14);
  u8g2.print("飞行员");
  u8g2.setCursor(0,38);  
  u8g2.print("请登录");

  u8g2.sendBuffer();
  u8g3.clearBuffer();
  u8g3.setFont(u8g2_font_wqy16_t_gb2312b);
  u8g3.setCursor(20, 14);
  u8g3.print("中国空军");
  u8g3.sendBuffer();


  // 在屏幕上画出空军图标，显示60秒钟    
  tft.fillScreen(BLACK);
  xpos = 0;
  ypos = 0;  
  rc = png.openFLASH((uint8_t *)PLA_airforce_icon, sizeof(PLA_airforce_icon), pngDraw);
  if (rc == PNG_SUCCESS) {
    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
    png.close();
   }
  xpos = 100;
  ypos = 180;  
  rc = png.openFLASH((uint8_t *)PLA_airforce_banner_small, sizeof(PLA_airforce_banner_small), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();
  delay(60000);

  //在屏幕上画出登录界面，显示5秒钟
  tft.fillScreen(BLACK);
  xpos = 0;
  ypos = 0;
  rc = png.openFLASH((uint8_t *)J20_login_1, sizeof(J20_login_1), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  // u8g2.setFont(u8g2_font_wqy14_t_gb2312);
  u8g2.setCursor(0,14);
  u8g2.print("请转动");
  u8g2.setCursor(0,38);  
  u8g2.print("头部");  
  u8g2.sendBuffer();
  delay(3000);
  
  rc = png.openFLASH((uint8_t *)J20_login_2, sizeof(J20_login_2), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  // u8g2.setFont(u8g2_font_wqy14_t_gb2312);
  u8g2.setCursor(0,14);
  u8g2.print("请眨眼");
  u8g2.setCursor(0,38);  
  u8g2.print("头部不动");  
  u8g2.sendBuffer();
  delay(3000);
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  // u8g2.setFont(u8g2_font_wqy14_t_gb2312);
  u8g2.setCursor(0,14);
  u8g2.print("人脸识别");
  u8g2.setCursor(0,38);  
  u8g2.print("成功");  
  u8g2.sendBuffer();
  delay(2000);

  //在屏幕上画出登录成功界面，显示5秒钟
  tft.fillScreen(BLACK);
  xpos = 0;
  ypos = 0;
  rc = png.openFLASH((uint8_t *)loged_in, sizeof(loged_in), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  // u8g2.setFont(u8g2_font_wqy14_t_gb2312);
  u8g2.setCursor(0,14);
  u8g2.print("刘培强");
  u8g2.setCursor(0,38);  
  u8g2.print("中校");  
  u8g2.sendBuffer();  
  delay(5000);

  //在屏幕上画出系统启动界面，显示5秒钟

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  // u8g2.setFont(u8g2_font_wqy14_t_gb2312);
  u8g2.setCursor(0,14);
  u8g2.print("犯我中华");
  u8g2.setCursor(0,38);  
  u8g2.print("虽远必诛");  
  u8g2.sendBuffer();  


  
  
  tft.fillScreen(BLACK);
  xpos = 0;
  ypos = 0;
  rc = png.openFLASH((uint8_t *)system_starting_1, sizeof(system_starting_1), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();
  delay(2000);
  rc = png.openFLASH((uint8_t *)system_starting_2, sizeof(system_starting_2), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();
  delay(2000);
  rc = png.openFLASH((uint8_t *)system_starting_3, sizeof(system_starting_3), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();
  delay(2000);


  // tft.fillScreen(BLACK);
  // xpos = 0;
  // ypos = 0;
  // rc = png.openFLASH((uint8_t *)beauty2, sizeof(beauty2), pngDraw);
  // tft.startWrite();
  // rc = png.decode(NULL, 0);
  // tft.endWrite();
  // png.close();
  // delay(3000);

  

  //显示飞行控制界面
  tft.fillScreen(BLACK);
  // 画出屏幕分割线
  // tft.drawRect(0,0,320,240,YELLOW);
  tft.drawRect(224,35,96,160,YELLOW);
  tft.drawRect(224,200,96,40,YELLOW);
  
  // tft.drawRect(0,0,10,10,YELLOW);
  // 通过像素，画出飞机中心指示标志
  
  //在屏幕上画出f35图
  xpos = 225;
  ypos = 40;
  rc = png.openFLASH((uint8_t *)j20_body_trans_2, sizeof(j20_body_trans_2), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();

//画出武器图标
  xpos = 235;
  ypos = 205;    
  rc = png.openFLASH((uint8_t *)missile_icon, sizeof(missile_icon), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();

//画出卫星图标
  xpos = 2;
  ypos = 2;    
  rc = png.openFLASH((uint8_t *)salt_icon, sizeof(salt_icon), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();
  
//画出电压图标
  xpos = 120;
  ypos = 2;    
  rc = png.openFLASH((uint8_t *)voltage_icon, sizeof(voltage_icon), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close();   
   
//画出速度图标
  xpos = 225;
  ypos = 2;    
  rc = png.openFLASH((uint8_t *)speed_meter_icon, sizeof(speed_meter_icon), pngDraw);
  tft.startWrite();
  rc = png.decode(NULL, 0);
  tft.endWrite();
  png.close(); 

 
   
}