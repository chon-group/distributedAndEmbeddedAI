#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/inertial_unit.h>
#include <webots/gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <javino.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <termios.h>
#include <math.h>

#define TIME_STEP 32
#define TTY_EXOGENOUS_PORT "/dev/ttyExogenous0"

typedef enum {
    LANDED,
    UP,
    DOWN,
    HOVERING,
    MOVE_RIGHT,
    MOVE_LEFT,
    LANDING,
    MOVE_FOWARD,
    MOVE_BACKWARD
} DroneState;

void clean_string(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
    for (char *p = str; *p; p++) *p = tolower(*p);
}

int main() {
    wb_robot_init();
    int timestep = wb_robot_get_basic_time_step();

    WbDeviceTag motors[4] = {
        wb_robot_get_device("front left propeller"),
        wb_robot_get_device("front right propeller"),
        wb_robot_get_device("rear left propeller"),
        wb_robot_get_device("rear right propeller"),
    };

    for (int i = 0; i < 4; i++) {
        if (motors[i] == 0) {
            printf("Motor %d não encontrado!\n", i);
        }
        wb_motor_set_position(motors[i], INFINITY);
        wb_motor_set_velocity(motors[i], 0.0);
    }

    // Sensores
    WbDeviceTag imu = wb_robot_get_device("inertial unit");
    WbDeviceTag gps = wb_robot_get_device("gps");

    if (imu == 0) printf("Sensor inercial não encontrado!\n");
    else wb_inertial_unit_enable(imu, timestep);

    if (gps == 0) printf("GPS não encontrado!\n");
    else wb_gps_enable(gps, timestep);

    // Configuração serial
    int serial = open(TTY_EXOGENOUS_PORT, O_RDWR | O_NOCTTY);
    if (serial < 0) {
        perror("Erro ao abrir porta serial");
        return 1;
    }

    struct termios tty;
    tcgetattr(serial, &tty);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag &= ~ICANON;
    tty.c_cc[VTIME] = 1;
    tty.c_cc[VMIN] = 0;
    tcsetattr(serial, TCSANOW, &tty);

    javino_init(serial);
    printf("Porta serial configurada\n");

    DroneState state = LANDED;

    double state_start_time = 0;

    double motor_speeds[4] = {0};


    //? ---------------------- Configs  ----------------------

    const double BASE_THRUST = 67.0;

    const double KP_STABILIZE = 50.0;
    const double KD_STABILIZE = 22.0;

    const double upThrust = 4.0;
    const double hoverThrust = 2.15;
    const double downThrust = -2.0;
    
    const double rightRoll = -0.025;
    const double leftRoll = 0.025;
    
    const double frontPitch = -0.025;
    const double backPitch = 0.025;
    
    const double landingThrust = -0.2;

    //? -------------------------------------------------------

    double last_roll = 0, last_pitch = 0;
    double initial_x = 0, initial_y = 0;

    printf("Calibrating Sensors...\n");
    for (int i = 0; i < 100; i++) {
        wb_robot_step(timestep);
        for (int j = 0; j < 4; j++) {
            wb_motor_set_velocity(motors[j], 0.0);
        }
    }
    printf("Calibration completed\n");
    
    while (wb_robot_step(timestep) != -1) {
        double current_time = wb_robot_get_time();
        double elapsed_time = current_time - state_start_time;

        double altitude = 0;
        double pos_x = 0, pos_y = 0, pos_z = 0;
        char percept[128];

        // Processamento de mensagens
        if (javino_avaliable_msg()) {
            char *msg = javino_get_msg();
            if (msg) {
                printf("Message Recieved: %s\n", msg);

                clean_string(msg);

                if (strcmp(msg, "up") == 0 && state != UP) {        
                    state = UP;
                    state_start_time = current_time;
                    printf("To infinity and beyond\n");

                    if (gps) {
                        const double *pos = wb_gps_get_values(gps);
                        initial_x = pos[0];
                        initial_y = pos[1];
                    }
                }  
                
                if (strcmp(msg, "down") == 0 && state != DOWN) {        
                    state = DOWN;
                    state_start_time = current_time;
                    printf("Going down\n");

                    if (gps) {
                        const double *pos = wb_gps_get_values(gps);
                        initial_x = pos[0];
                        initial_y = pos[1];
                    }
                }  

                else if (strcmp(msg, "land") == 0 && state != LANDED) {
                    state = LANDING;
                    state_start_time = current_time;
                    printf("Landing!!\n");
                } 

                else if (strcmp(msg, "right") == 0 && state != MOVE_RIGHT) {
                    state = MOVE_RIGHT;
                    state_start_time = current_time;
                    printf("Going Right\n");

                    if (gps) {
                        const double *pos = wb_gps_get_values(gps);
                        initial_x = pos[0];
                        initial_y = pos[1];
                    }
                } 

                else if (strcmp(msg, "left") == 0 && state != MOVE_LEFT) {
                    state = MOVE_LEFT;
                    state_start_time = current_time;
                    printf("Going Left!\n");

                    if (gps) {
                        const double *pos = wb_gps_get_values(gps);
                        initial_x = pos[0];
                        initial_y = pos[1];
                    }
                }

                else if (strcmp(msg, "forward") == 0 && state != MOVE_FOWARD) {
                    state = MOVE_FOWARD;
                    state_start_time = current_time;
                    printf("Forwards!\n");

                    if (gps) {
                        const double *pos = wb_gps_get_values(gps);
                        initial_x = pos[0];
                        initial_y = pos[1];
                    }
                }
                    else if (strcmp(msg, "backward") == 0 && state != MOVE_BACKWARD) {
                    state = MOVE_BACKWARD;
                    state_start_time = current_time;
                    printf("Backwards!\n");

                    if (gps) {
                        const double *pos = wb_gps_get_values(gps);
                        initial_x = pos[0];
                        initial_y = pos[1];
                    }
                }

                else if (strcmp(msg, "off") == 0 && state != LANDED) {
                    state = LANDED;
                    state_start_time = current_time;
                    printf("Turning off!!!\n");
                } 

                else if (strcmp(msg, "hover") == 0 && state != HOVERING) {
                    state = HOVERING;
                    state_start_time = current_time;
                    printf("Hovering!\n");
                } 
                
                else {
                    printf("Not a command or already in execution\n");
                }
                
                free(msg);
            }
        }

        double roll = 0, pitch = 0;

        if (imu) {
            const double *rpy = wb_inertial_unit_get_roll_pitch_yaw(imu);
            roll = rpy[0];
            pitch = rpy[1];
        }

        if (gps) {
            const double *pos = wb_gps_get_values(gps);
            pos_x = pos[0];
            pos_y = pos[1];
            pos_z = pos[2];
            altitude = pos_z;

            static int step_counter = 0;
            step_counter++;
            
            int init = 0;
            int maxCounter = 250;

            if (step_counter >= maxCounter) {
                
                snprintf(percept, sizeof(percept), "gps(%.2f,%.2f,%.2f);", pos_x, pos_y, pos_z);
                javino_send_msg(percept);

                printf("INITIAL GPS sended: gps(%.2f,%.2f,%.2f)\n", pos_x, pos_y, pos_z);
                
                init = 1;
                step_counter = 0;
            }

        }

        double roll_rate = (roll - last_roll) / (timestep / 1000.0);
        double pitch_rate = (pitch - last_pitch) / (timestep / 1000.0);
        last_roll = roll;
        last_pitch = pitch;

        double thrust_correction = 0;
        double roll_correction = 0;
        double pitch_correction = 0;

        switch (state) {

            //? Default values:
            /*
              const double BASE_THRUST = 67.0;

                const double KP_STABILIZE = 50.0;
                const double KD_STABILIZE = 22.0;

                const double upThrust = 4.0;
                const double hoverThrust = 2.15;
                const double downThrust = -4.0;
                
                const double rightRoll = -0.1;
                const double leftRoll = 0.1;
                
                const double frontPitch = -0.1;
                const double backPitch = 0.1;
                
                const double landingThrust = -0.2;
            */
            
            case LANDED: {
                for (int i = 0; i < 4; i++) {
                    wb_motor_set_velocity(motors[i], 0.0);
                }
                break;
            }

            case UP: {
                roll = 0, pitch = 0;
                roll_correction = 0;
                pitch_correction = 0;

                thrust_correction = upThrust;
                 
                break;
            }
            
            case DOWN:{
                roll = 0 ;
                pitch = 0;
                roll_correction = 0;
                pitch_correction = 0;
    
                thrust_correction = downThrust;
                 
                break;
            }

            case HOVERING: {
                roll_correction = 0;
                pitch_correction = 0;                
                
                thrust_correction = hoverThrust;
    
                break;
            }

            case MOVE_RIGHT: {
                roll = 0;
                pitch = 0;
                pitch_correction = 0;
                roll_correction = 0;
                
                thrust_correction = hoverThrust;
                roll = rightRoll;

                break;
            }
            
            case MOVE_LEFT: {
                roll = 0;
                roll_correction = 0;
                pitch_correction = 0;     
                
                thrust_correction = hoverThrust;
                roll = leftRoll;

                break;
            }

            case MOVE_FOWARD: {
                roll = 0;
                roll_correction = 0;
                pitch_correction = 0;       
                
                thrust_correction = hoverThrust;
                pitch = frontPitch;

                break;
            }

            case MOVE_BACKWARD: {
                roll = 0;
                roll_correction = 0;
                pitch_correction = 0;
                
                thrust_correction = hoverThrust;
                pitch = backPitch;

                break;
            }


            case LANDING: {
                roll = 0, pitch = 0;
                roll_correction = 0;
                pitch_correction = 0;

                thrust_correction = landingThrust;

                break;
            }
        
        }

        if (state != LANDED) {
            roll_correction += KP_STABILIZE * (-roll) + KD_STABILIZE * (-roll_rate);
            pitch_correction += KP_STABILIZE * (-pitch) + KD_STABILIZE * (-pitch_rate);

            motor_speeds[0] = BASE_THRUST + thrust_correction - pitch_correction + roll_correction;
            motor_speeds[1] = BASE_THRUST + thrust_correction - pitch_correction - roll_correction;
            motor_speeds[2] = BASE_THRUST + thrust_correction + pitch_correction + roll_correction;
            motor_speeds[3] = BASE_THRUST + thrust_correction + pitch_correction - roll_correction;

            // Limites
            for (int i = 0; i < 4; i++) {
                if (motor_speeds[i] > 100.0) motor_speeds[i] = 100.0;
                if (motor_speeds[i] < 5.0) motor_speeds[i] = 5.0;
            }

            wb_motor_set_velocity(motors[0], motor_speeds[0]);
            wb_motor_set_velocity(motors[1], -motor_speeds[1]);
            wb_motor_set_velocity(motors[2], -motor_speeds[2]);
            wb_motor_set_velocity(motors[3], motor_speeds[3]);
        }
        static double last_debug = 0;
        static double last_hover = 0;

        double quantumStableSeconds = 5;
        
        //? -------------- Hover controll --------------
        if (current_time - last_hover > quantumStableSeconds && state != LANDING && state != LANDED ) { //TODO: EQUALIZAR COM O AGENTE
            printf("Estabilizando \n");

            state = HOVERING;

            last_hover = current_time;
            quantumStableSeconds = 1;
        } 

        //? -------------- Debug controll --------------   

        if (current_time - last_debug > 5) {
            printf("Estado: %d | Altura: %.2fm | X: %.2f | Y: %.2f\n",
                   state, altitude, pos_x, pos_y);
            last_debug = current_time;
        } 

    }

    close(serial);
    wb_robot_cleanup();
    return 0;
}
