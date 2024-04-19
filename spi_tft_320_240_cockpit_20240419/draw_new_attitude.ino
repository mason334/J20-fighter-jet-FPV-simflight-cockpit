void draw_new_attitude(){

  //覆盖原姿态线
  spr.fillRect(1,1,x_limit-1,y_limit-1,GREEN);  
  spr.fillTriangle(xb5,yb5,xb6,yb6,xb7,yb7,BLUE);
  spr.fillTriangle(xb8,yb8,xb6,yb6,xb7,yb7,BLUE);
  

  
// 画出i范围level的新的姿态线, i的范围是0-6，

  spr.drawRect(0,0,x_limit,y_limit,YELLOW);//画出姿态线的框框
  spr.fillTriangle(x_center, y_center,x_center-35,y_center+9,x_center+35,y_center+9, RED);//画出飞机标记
  // Serial.println("Pitch, Roll");
  // Serial.print(pitch);Serial.println(roll); 




  
  for (int i=1; i < 6; i++) {
       
    draw_level_angle = base_vect*level_angle+(i-3)*level_angle;
    if (draw_level_angle < 0){
      color = BLACK;      
      // Serial.print("draw_level_angle: ");Serial.println(draw_level_angle);
      // Serial.println(att_points[i][0]);
      // Serial.println(att_points[i][1]);
      // Serial.println(att_points[i][2]);
      // Serial.println(att_points[i][3]);
    } else{
      color = WHITE;
    }
    
    itoa(draw_level_angle, level_char, 10);        
    if ((draw_level_angle == 0) && (xb1>1) && (xb1<x_limit) && (xb2>1) && (xb2<x_limit) && (yb1>1) && (yb1<y_limit) && (yb2>1)  && (yb2<y_limit)){
      spr.drawLine(xb1, yb1, xb2, yb2,color); //画一根长的地平线
    } else {
        if((att_points[i][0]>1) && (att_points[i][0]<x_limit) && (att_points[i][1]>1)  && (att_points[i][1]<y_limit) && (att_points[i][2]>1) && (att_points[i][2]<x_limit)  && (att_points[i][3]>1) && (att_points[i][3]<y_limit) ) {
          spr.drawLine(att_points[i][0], att_points[i][1], att_points[i][2], att_points[i][3],color);
        }       
      } //else
    // 写上pitch度数    
    spr.setCursor((att_points[i][0]+att_points[i][6])/2, (att_points[i][1]+att_points[i][7])/2);
    spr.setTextColor(color);
    spr.println(level_char);
    
    if ((draw_level_angle == 0) && (xb3>1) && (xb4>1) && (xb3<x_limit) && (xb4<x_limit) && (yb3>1) && (yb4>1) && (yb3<y_limit) && (yb4<y_limit) ){
      spr.drawLine(xb3, yb3, xb4, yb4,color); //画一根长的地平线
      } else {
        if((att_points[i][4]>1) && (att_points[i][4]<x_limit) && (att_points[i][5]>1)  && (att_points[i][5]<y_limit) && (att_points[i][6]>1) && (att_points[i][6]<x_limit)  && (att_points[i][7]>1) && (att_points[i][7]<y_limit) )  {          
          spr.drawLine(att_points[i][4], att_points[i][5], att_points[i][6], att_points[i][7],color);
          
        }
      }//else   
    // 写上pitch度数
    spr.setCursor((att_points[i][0]+att_points[i][6])/2, (att_points[i][1]+att_points[i][7])/2);
    spr.setTextColor(color);
    spr.println(level_char);    
    // delay(5000);    
  } // for loop
 
  // memcpy(old_att_points, att_points, 7*8*sizeof(att_points[0][0]));
  // old_xb1=xb1 , old_xb2=xb2, old_xb3=xb3, old_xb4=xb4, old_yb1=yb1, old_yb2=yb2, old_yb3=yb3, old_yb4=yb4;
  // old_base_vect = base_vect;
  //记得手动改颜色
}