// mavlink msg https://github.com/mavlink/c_library_v1/tree/master/common
// 或者在\Arduino\libraries\mavlink\common 里面也能找到msg的定义

void get_mavlink_data(){
  uint32_t max_packets = 10; // 限制每次处理的最大包数
  uint32_t packet_count = 0;
  
  while (Serial.available() > 0 && packet_count < max_packets) {
    // Serial.read前不能有任何干扰串口信息，比如往串口发送信息的Serial.print,否则会干扰串口数据。
    uint8_t result = Serial.read(); // 读取串口信息，假设此时串口已经开始发送信息///
    msgReceived = mavlink_parse_char(MAVLINK_COMM_1, result, &msg, &status);
    if (msgReceived) {
      packet_count++;
      mavlink_data_ready = true;  // 设置数据就绪标志
      // Serial.print("Msgid: ");  Serial.println(msg.msgid);
      switch (msg.msgid) {  
        case MAVLINK_MSG_ID_HEARTBEAT:  // #0
        {
          mavlink_heartbeat_t heart;
          mavlink_msg_heartbeat_decode(&msg, &heart);
          base_mode = heart.base_mode;
          custom_mode = heart.custom_mode;
          flight_mode = custom_mode + base_mode;
          system_status = heart.system_status;
          switch(system_status){
            case 3:
              system_status_str = "待命";
              break;
            case 4:
              system_status_str = "运行中";
              break;
            case 5:
              system_status_str = "锁定";
              break;
          }  
          switch (custom_mode){
            case 11:
              flight_mode_str = "返航";
              break;
            case 5:
              flight_mode_str = "巡航";
              break;
            case 0:
              flight_mode_str = "手动";
              break;
            case 4:
              flight_mode_str = "战斗";
              break;
            case 13:
              flight_mode_str = "弹射起飞";
              break;
          }

          break;           
        }

        // case MAVLINK_MSG_ID_AVAILABLE_MODES:
        // {
        //   mavlink_available_modes_t available_modes;
        //   mavlink_msg_heartbeat_decode(&msg, &available_modes);
        //   mode_index = available_modes.mode_index;
        // }

        case MAVLINK_MSG_ID_SYS_STATUS:  // #1
          {
            mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&msg, &sys_status);
            voltage_battery = sys_status.voltage_battery;
            current_battery = sys_status.current_battery;
            break;          
          }
        
        case MAVLINK_MSG_ID_DISTANCE_SENSOR:// 132
        {
          mavlink_distance_sensor_t rangefinder;
          mavlink_msg_distance_sensor_decode(&msg, &rangefinder);
          current_distance = rangefinder.current_distance;
          rangefinder_distance = current_distance/100;
          break; 
        }

        case MAVLINK_MSG_ID_BATTERY_STATUS:  // #147
          {
            mavlink_battery_status_t batt_status;
            mavlink_msg_battery_status_decode(&msg, &batt_status);
            current_consumed = batt_status.current_consumed;
            break;          
          }
        
        case MAVLINK_MSG_ID_GPS_RAW_INT: // #24  
          {
            mavlink_gps_raw_int_t  gps_raw_int;
            mavlink_msg_gps_raw_int_decode(&msg, &gps_raw_int);   
            satellites_visible = gps_raw_int.satellites_visible; 
            cog = gps_raw_int.cog;
            break;                  
          }        
              
        case MAVLINK_MSG_ID_ATTITUDE:  // #30
          {
            mavlink_attitude_t attitude;
            mavlink_msg_attitude_decode(&msg, &attitude);
            pitch = attitude.pitch;
            roll = -attitude.roll;
            yaw = attitude.yaw;   
            break;                     
          }
        
        
        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:  // #33
          {
            mavlink_global_position_int_t global_position_int;
            mavlink_msg_global_position_int_decode(&msg, &global_position_int);
            time_boot_ms = global_position_int.time_boot_ms;
            relative_alt = global_position_int.relative_alt/1000;
            hdg = global_position_int.hdg; /*< [cdeg] Vehicle heading (yaw angle), 0.0..359.99 degrees. If unknown, set to: UINT16_MAX*/
            break; 
          }
          
        case MAVLINK_MSG_ID_REQUEST_DATA_STREAM: //66
          {
            mavlink_request_data_stream_t r_stream_t;
            mavlink_msg_request_data_stream_decode (&msg, &r_stream_t);
            req_message_rate =  r_stream_t.req_message_rate;
            break; 
          } 
                 
        case MAVLINK_MSG_ID_DATA_STREAM: // 67
          { 
            mavlink_data_stream_t stream_t;
            mavlink_msg_data_stream_decode (&msg, &stream_t);
            message_rate = stream_t.message_rate;
            stream_id = stream_t.stream_id;       
            on_off = stream_t.on_off;
            break; 
          }
        
        
        
        case MAVLINK_MSG_ID_VFR_HUD:  // #74
          {
            mavlink_vfr_hud_t vfr_hud;
            mavlink_msg_vfr_hud_decode(&msg, &vfr_hud);
            airspeed = vfr_hud.airspeed; /*< [m/s] Vehicle speed. */
            groundspeed = vfr_hud.groundspeed; /*< [m/s] Current ground speed.*/
            alt = vfr_hud.alt; /*< [m] Current altitude (MSL).*/            
            climb = vfr_hud.climb; /*< [m/s] Current climb rate.*/
            heading = vfr_hud.heading; //[deg] Current heading in compass units (0-360, 0=north).
            throttle = vfr_hud.throttle; /*< [%] Current throttle setting (0 to 100).*/
            break; 
          }
        
        case MAVLINK_MSG_ID_RC_CHANNELS_RAW: //needs mavlink V1 to get this data
          {
            mavlink_rc_channels_raw_t rc_channels_raw;
            mavlink_msg_rc_channels_raw_decode(&msg, &rc_channels_raw);
              // chan1_raw = rc_channels_raw.chan1_raw;
              // chan2_raw = rc_channels_raw.chan2_raw;
              // chan3_raw = rc_channels_raw.chan3_raw;
              // chan4_raw = rc_channels_raw.chan4_raw;
              // chan5_raw = rc_channels_raw.chan5_raw;
            // chan6_raw = rc_channels_raw.chan6_raw;
            chan7_raw = rc_channels_raw.chan7_raw;
              // chan8_raw = rc_channels_raw.chan8_raw;
              // rc_channels_raw.port = port;
            // rssi = rc_channels_raw.rssi;
            break; 
          }
        case MAVLINK_MSG_ID_RADIO_STATUS:
          {
            mavlink_radio_status_t radio_status;
            mavlink_msg_radio_status_decode(&msg, &radio_status);
            rssi = radio_status.rssi;
            break; 
          }

                  
      }//switch (message.msgid)         
    }//if (msgReceived)    
  }//while (Serial.available() > 0)
}