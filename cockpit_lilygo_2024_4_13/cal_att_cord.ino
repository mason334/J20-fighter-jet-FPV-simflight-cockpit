void cal_att_cord(){

  //计算pitch后r0长度
  r0 = pitch*pitch_to_pixel;
  alpha = HALF_PI + roll;
  beta = HALF_PI + alpha;
  cosa = cos(alpha);
  sina = sin(alpha);
  cosb = cos(beta);
  sinb = sin(beta);
    
  x0 = r0*cosa + x_center; //0度姿态线中点横坐标
  y_0 = r0*sina + y_center; //0度姿态线中点纵坐标
  vx = level_pixel*cosa;
  vy = level_pixel*sina;

  center_degree = (pitch)/PI*180; //把幅度pitch换算成角度
  base_vect = round(center_degree/level_angle); // x0,y_0到姿态仪中心点有几条姿态线，  
  //0度姿态线坐标
  xa1 = x0+cosb*r1;
  ya1 = y_0+sinb*r1;
  xa2 = x0+cosb*r2;
  ya2 = y_0+sinb*r2;  
  xa3 = x0-cosb*r3;
  ya3 = y_0-sinb*r3;
  xa4 = x0-cosb*r4;
  ya4 = y_0-sinb*r4;

  //计算姿态仪中心姿态线坐标，也就是第四行坐标：att_points[3]
  att_points[3][0] = xa1-vx*base_vect;
  att_points[3][1] = ya1-vy*base_vect;
  att_points[3][2] = xa2-vx*base_vect;
  att_points[3][3] = ya2-vy*base_vect;
  att_points[3][4] = xa3-vx*base_vect;
  att_points[3][5] = ya3-vy*base_vect;
  att_points[3][6] = xa4-vx*base_vect;
  att_points[3][7] = ya4-vy*base_vect;
  
  //根据姿态仪中心姿态线坐标，计算其他几条姿态线坐标
  for (int i=0; i < 7; i++) {      
  int j = i-3;//j用于标记姿态线距离姿态仪中心姿态线的距离, i用于标记姿态线，最pitch最高的一根编号为0，最低的编号为6，姿态仪中心姿态线坐标编号为3
  att_points[i][0] = att_points[3][0]-j*vx;   att_points[i][1] = att_points[3][1]-j*vy;     
  att_points[i][2] = att_points[3][2]-j*vx;   att_points[i][3] = att_points[3][3]-j*vy;  
  att_points[i][4] = att_points[3][4]-j*vx;   att_points[i][5] = att_points[3][5]-j*vy;
  att_points[i][6] = att_points[3][6]-j*vx;   att_points[i][7] = att_points[3][7]-j*vy;
  }  
 
  //长的0度地平线坐标
  xb1 = x0+cosb*l1;
  yb1 = y_0+sinb*l1;
  xb2 = x0+cosb*l2;
  yb2 = y_0+sinb*l2;  
  xb3 = x0-cosb*l3;
  yb3 = y_0-sinb*l3;
  xb4 = x0-cosb*l4;  
  yb4 = y_0-sinb*l4;  
  
  //b5 b6 b7 b8 构成了天空框， b5->b7, b6->b8
  xb5 = x0+cosb*l0;
  yb5 = y_0+sinb*l0;
  xb6 = x0-cosb*l0;
  yb6 = y_0-sinb*l0;    
  xb7 = x0+cosb*l0-9*vx;
  yb7 = y_0+sinb*l0-9*vy;
  xb8 = x0-cosb*l0-9*vx;
  yb8 = y_0-sinb*l0-9*vy;  


  

}