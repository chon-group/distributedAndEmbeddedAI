#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include <stdio.h>

#include <javino.h>
/**
 * This test requires the installation of the SerialPortEmulator project
 * 
 * */ 

int main(int argc, char **argv){

    if (argc != 3 ){

        printf("Usage: %s [emulated port path] [exogenous path]\n",
            argv[0]);

        return -1;
    }

    char *exogenous_path = argv[1];
    char *emulated_port_path = argv[2];

    int exogenous = open(exogenous_path, O_RDWR);
    if (exogenous == -1){
        perror(NULL);

        return -1;
    }

    int emulated_port = open(emulated_port_path, O_RDWR);

    pid_t pid;

    if ( (pid = fork()) ){

        // Child process: waits

        javino_init( exogenous );

        javino_send_msg( "Test 01" );

        javino_exit();

        return 0;

    } else {

        // `Parent process: waits the child for the wrote

        javino_init( emulated_port );

        while ( !javino_avaliable_msg() ){

            sched_yield();

        }

        char *recv_msg = javino_get_msg();

        fprintf(stderr, "\nTest 01: %s", recv_msg);

        javino_exit();

    }



    return 0;
}