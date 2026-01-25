/*
 * Copyright 1996-2023 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include <javino.h>

// time in [ms] of a simulation step
#define TIME_STEP 20

#define TTY_EXOGENOUS_PORT "/dev/ttyExogenous0"

#define LOG "/tmp/robot.log"


// entree point of the controller
int main(int argc, char **argv) {

  static int reasoning_cycle = 1;
  char percepts_msg[262];  

 
  // initialise the Webots API
  wb_robot_init();

  // internal variables
  int i;

  // initialise distance sensors
  WbDeviceTag ds[2];
  char ds_names[2][10] = {"ds_left", "ds_right"};
  for (i = 0; i < 2; i++) {
    ds[i] = wb_robot_get_device(ds_names[i]);
    wb_distance_sensor_enable(ds[i], TIME_STEP);
  }

  
  // initialise motors
  WbDeviceTag wheels[4];
  
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (i = 0; i < 4; i++) {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }
  
  
  int exogenous_port =  open(
    TTY_EXOGENOUS_PORT,
    O_RDWR
    );
    
  javino_init( exogenous_port );
  
  char *javino_received_msg;
  
  double left_speed = 0.0;
  double right_speed = 0.0;
  
  wb_motor_set_velocity(wheels[0], left_speed);
  wb_motor_set_velocity(wheels[1], right_speed);
  wb_motor_set_velocity(wheels[2], left_speed);
  wb_motor_set_velocity(wheels[3], right_speed);  

  // feedback loop
  while (wb_robot_step(TIME_STEP) != -1) {
    // init speeds
    
    int javino_has_message = avaliable_msg();
    
    if (! javino_has_message ){
    
      continue;
    }
    
    javino_received_msg = javino_get_msg( );
    
    fprintf(stderr, "\njavino_received_msg: %s", 
      javino_received_msg ); 
    
    if ( ! strcmp( javino_received_msg , "getPercepts" )  ){
      
      // Distance sensor value
      float d1 = wb_distance_sensor_get_value( ds[0] );
      
      float d2 = wb_distance_sensor_get_value( ds[1] );
        
      // printf("\n %.1f %.1f", d1, d2 );
            
      // Composing percepts message to send to Javino
      int nbytes_written = sprintf(percepts_msg, 
        "dLeft(%.1f);dRight(%.1f);",
        d1, d2 );
        
       if ( nbytes_written == -1 ){
       
         fprintf(stderr, "\nERROR: Couldn't compose perception strings!");
         
       } else {
       
         // fprintf(stderr, "\n%s\n", percepts_msg);
         
       }
       
      fprintf(stdout,
        "\nReceived: getPercepts (%d) = %s\n",
        reasoning_cycle++, 
        percepts_msg);

        //left_speed = 0.0;
        //right_speed = 0.0;                         
        
        //wb_motor_set_velocity(wheels[0], left_speed);
        //wb_motor_set_velocity(wheels[1], right_speed);
        //wb_motor_set_velocity(wheels[2], left_speed);
        //wb_motor_set_velocity(wheels[3], right_speed);             
       
       nbytes_written = javino_send_msg(
         exogenous_port,
         percepts_msg);
         
       if ( (strlen(percepts_msg) + JAVINO_HEADER_LEN) != nbytes_written ){
         
         fprintf(stderr, 
           "\nError! Message length plus header (%lu) different from sent by Javino!(%u)!",
           (strlen(percepts_msg) + JAVINO_HEADER_LEN),
           nbytes_written );
              
       }     
       
      free( javino_received_msg );        
                                                      
    } else if ( ! strcmp( javino_received_msg , "goAhead" ) ){
    
      fprintf(stdout, 
        "\nReceived: goAhead (%d)\n",
        reasoning_cycle++ );
    
      left_speed = 1.0;
      right_speed = 1.0; 
      
      wb_motor_set_velocity(wheels[0], left_speed);
      wb_motor_set_velocity(wheels[1], right_speed);
      wb_motor_set_velocity(wheels[2], left_speed);
      wb_motor_set_velocity(wheels[3], right_speed);  
      
      free( javino_received_msg );                
          
    } else if ( ! strcmp( javino_received_msg , "goRight" ) ){
    
      fprintf( stdout,
        "\nReceived: goRight (%d)\n",
        reasoning_cycle++ );
    
      left_speed = 1.0;
      right_speed = 0.0;
      
      wb_motor_set_velocity(wheels[0], left_speed);
      wb_motor_set_velocity(wheels[1], right_speed);
      wb_motor_set_velocity(wheels[2], left_speed);
      wb_motor_set_velocity(wheels[3], right_speed); 
      
      free( javino_received_msg );                
    
    } else if ( ! strcmp( javino_received_msg , "goBack" ) ){
    
      fprintf(stdout, 
        "\nReceived: goBack (%d)\n",
        reasoning_cycle++ );
    
      left_speed = -1.0;
      right_speed = -1.0;  
      
      
      wb_motor_set_velocity(wheels[0], left_speed);
      wb_motor_set_velocity(wheels[1], right_speed);
      wb_motor_set_velocity(wheels[2], left_speed);
      wb_motor_set_velocity(wheels[3], right_speed);  
      
            free( javino_received_msg );                     
    
    } else {
    
      fprintf(stderr, 
        "\nWARNING: unknown received reasoning (%d): (%s) \n",
        reasoning_cycle++,
        javino_received_msg ); 
    
    }
    
 
    
/*    
    if (avoid_obstacle_counter > 0) {
    
      avoid_obstacle_counter--;
      left_speed = 1.0;
      right_speed = -1.0;
      
    } else {
      // read sensors outputs
      
      double ds_values[2];
      for (i = 0; i < 2; i++)
        ds_values[i] = wb_distance_sensor_get_value(ds[i]);

      // increase counter in case of obstacle
      if (ds_values[0] < 950.0 || ds_values[1] < 950.0)
        avoid_obstacle_counter = 100;
    }
*/    

    // write actuators inputs

  }

  // cleanup the Webots API
  wb_robot_cleanup();
  return 0;  // EXIT_SUCCESS
}
