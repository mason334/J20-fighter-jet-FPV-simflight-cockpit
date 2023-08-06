void get_mavlink_data(){
  while (Serial.available() > 0) {
    // Serial.read前不能有任何干扰串口信息，比如往串口发送信息的Serial.print,否则会干扰串口数据。
    uint8_t result = Serial.read(); // 读取串口信息，假设此时串口已经开始发送信息///
    msgReceived = mavlink_parse_char(MAVLINK_COMM_1, result, &msg, &status);
    if (msgReceived) {
      // Serial.print("Msgid: ");  Serial.println(msg.msgid);
      switch (msg.msgid) {  
        // case MAVLINK_MSG_ID_HEARTBEAT:
        //   {
        //     mavlink_heartbeat_t hb;
        //     mavlink_msg_heartbeat_decode(&message, &hb);
        //     Serial.print("\n");
        //     Serial.println("Heartbeat Message");
        //     Serial.print("Msgid: ");  Serial.println(message.msgid);
        //     Serial.print("Type: ");  Serial.println(hb.type);
        //     Serial.print("Autopilot type: ");  Serial.println(hb.autopilot);
        //     Serial.print("System mode: ");  Serial.println(hb.base_mode);
        //     Serial.print("Custom mode: ");  Serial.println(hb.custom_mode);
        //     Serial.print("System status: ");  Serial.println(hb.system_status);
        //     Serial.print("Mavlink version: "); Serial.println(hb.mavlink_version);
        //     delay(1000);
        //   }

        case MAVLINK_MSG_ID_SYS_STATUS:  // #1
          {
            /* Message decoding: PRIMITIVE
            *    mavlink_msg_attitude_decode(const mavlink_message_t* msg, mavlink_attitude_t* attitude)
            */
            mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&msg, &sys_status);
            voltage_battery = sys_status.voltage_battery;
            battery_remaining = sys_status.battery_remaining;
            current_battery = sys_status.current_battery;
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
            /* Message decoding: PRIMITIVE
            *    mavlink_msg_attitude_decode(const mavlink_message_t* msg, mavlink_attitude_t* attitude)
            */
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
            relative_alt = global_position_int.relative_alt;
            hdg = global_position_int.hdg; /*< [cdeg] Vehicle heading (yaw angle), 0.0..359.99 degrees. If unknown, set to: UINT16_MAX*/
            break; 
          }
          
        // case MAVLINK_MSG_ID_REQUEST_DATA_STREAM: //66
        //   {
        //     mavlink_request_data_stream_t stream_t;
        //     mavlink_msg_data_stream_decode (&msg, &stream_t);              
        //   } 
                 
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
            airspeed = vfr_hud.airspeed;
            groundspeed = vfr_hud.groundspeed;
            alt = vfr_hud.alt;
            climb = vfr_hud.climb;
            heading = vfr_hud.heading; //[deg] Current heading in compass units (0-360, 0=north).
            throttle = vfr_hud.throttle; 
            break; 
          }
                  
      }//switch (message.msgid)         
    }//if (msgReceived)    
  }//while (Serial.available() > 0)
}