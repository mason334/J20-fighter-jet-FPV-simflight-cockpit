void draw_new_attitude(){

  //覆盖原姿态线
  spr.fillRect(1,1,x_limit-1,y_limit-1,GREEN);  
  spr.fillTriangle(xb5,yb5,xb6,yb6,xb7,yb7,BLUE);
  spr.fillTriangle(xb8,yb8,xb6,yb6,xb7,yb7,BLUE);
  spr.loadFont(NotoSansMonoSCB20);  

  
// 画出i范围level的新的姿态线, i的范围是0-6，

  spr.drawRect(0,0,x_limit,y_limit,YELLOW);//画出姿态线的框框
  spr.fillTriangle(x_center, y_center,x_center-35,y_center+9,x_center+35,y_center+9, RED);//画出飞机标记
  
  for (int i=1; i < 6; i++) {
    //base_vect*level_angle得到离姿态仪中心最近的姿态线角度
    draw_level_angle = base_vect*level_angle+(i-3)*level_angle; // i-3 在for循环中，得到-2，-1， 0， 1, 2 三根姿态线编号，0号姿态线就是离姿态仪中心最近的姿态线
    if (draw_level_angle < 0){
      color = BLACK;      
    } else{
      color = WHITE;
    }
    
    itoa(draw_level_angle, level_char, 10);        
    //判断长的0度地平线左边一半线段坐标是否在画布范围内
    if ((draw_level_angle == 0) && (xb1>1) && (xb1<x_limit) && (xb2>1) && (xb2<x_limit) && (yb1>1) && (yb1<y_limit) && (yb2>1)  && (yb2<y_limit)){
      spr.drawWideLine(xb1, yb1, xb2, yb2, 4, color); //画一根长的地平线
    } else {
        if((att_points[i][0]>1) && (att_points[i][0]<x_limit) && (att_points[i][1]>1)  && (att_points[i][1]<y_limit) && (att_points[i][2]>1) && (att_points[i][2]<x_limit)  && (att_points[i][3]>1) && (att_points[i][3]<y_limit) ) {
          spr.drawWideLine(att_points[i][0], att_points[i][1], att_points[i][2], att_points[i][3], 4, color);
        }       
      } //else

    //判断长的0度地平线右边一半线段坐标是否在画布范围内
    if ((draw_level_angle == 0) && (xb3>1) && (xb4>1) && (xb3<x_limit) && (xb4<x_limit) && (yb3>1) && (yb4>1) && (yb3<y_limit) && (yb4<y_limit) ){
      spr.drawWideLine(xb3, yb3, xb4, yb4, 4, color); //画一根长的地平线
      } else {
        if((att_points[i][4]>1) && (att_points[i][4]<x_limit) && (att_points[i][5]>1)  && (att_points[i][5]<y_limit) && (att_points[i][6]>1) && (att_points[i][6]<x_limit)  && (att_points[i][7]>1) && (att_points[i][7]<y_limit) )  {          
          spr.drawWideLine(att_points[i][4], att_points[i][5], att_points[i][6], att_points[i][7], 4, color);
          
        }
      }//else  

    // *****************写上pitch度数**********************
    if (draw_level_angle == 0 ){
      spr.setCursor((att_points[i][0]+att_points[i][6])/2 - 5, (att_points[i][1]+att_points[i][7])/2 - 10);
      spr.setTextColor(color);
      spr.println(level_char);    
    }
    if (draw_level_angle > 0 ){
      spr.setCursor((att_points[i][0]+att_points[i][6])/2 - 10, (att_points[i][1]+att_points[i][7])/2 - 10);
      spr.setTextColor(color);
      spr.println(level_char);    
    }
    if (draw_level_angle < 0 ){
      spr.setCursor((att_points[i][0]+att_points[i][6])/2 - 15, (att_points[i][1]+att_points[i][7])/2 - 10);
      spr.setTextColor(color);
      spr.println(level_char);    
    }

  } // for loop
  spr.unloadFont();
  // memcpy(old_att_points, att_points, 7*8*sizeof(att_points[0][0]));
  // old_xb1=xb1 , old_xb2=xb2, old_xb3=xb3, old_xb4=xb4, old_yb1=yb1, old_yb2=yb2, old_yb3=yb3, old_yb4=yb4;
  // old_base_vect = base_vect;
  //记得手动改颜色
}


