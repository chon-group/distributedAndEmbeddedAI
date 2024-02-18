#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <javino.h>


int main(int argc, char **argv){

	if (argc < 3){
		fprintf(stderr, "Invalid number of parameters");
		return -1;
	}

	char *port = argv[ 1 ];
	char *message = argv[ 2 ];

	javino_send_msg(port, message);	
		
	return 0;
}
