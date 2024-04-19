void push_u8g1_fps1() 
{
// 用中间2屏幕来显示FPS
    now2 = millis();
    if (now2 - Millis2nd >= 100){      
      Millis2nd = now2;             
      u8g1.clearBuffer();
      u8g1.setCursor(0,14);
      u8g1.print("fps3: ");
      u8g1.setCursor(40,14);
      u8g1.print(fps3);      
      u8g1.setCursor(0,38);  
      u8g1.print("fps1: ");
      u8g1.setCursor(40,38);
      u8g1.print(fps1);      
      u8g1.sendBuffer();      
    }
}

void push_u8g2_radar() 
{
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
      degreeRadar = degreeRadar + 10;
      if (degreeRadar > 360) {
        degreeRadar = degreeRadar - 360;        
      }   
}

void push_u8g1_current() 
{
    u8g1.clearBuffer();
    u8g1.setCursor(20, 14);   
    u8g1.print("动力");
    u8g1.print(double(current_battery)/100, 2);
    u8g1.sendBuffer();
}

void push_u8g2_fltmode()
{
  u8g2.clearBuffer();
  u8g2.setCursor(0, 16); 
  u8g2.print("飞行模式:");
  u8g2.setCursor(0, 36);
  u8g2.print(flight_mode_str);
  u8g2.sendBuffer();
}