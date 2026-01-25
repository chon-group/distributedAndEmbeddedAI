#include <stdio.h>
#include <stdlib.h>

#include <javino.h>

int main(int argc, char **argv){

	if (argc != 2){
		fprintf(stderr, "Invalid number of parameters");
		return -1;
	}

	char *port = argv[1];

	char *msg = javino_get_msg(port);

	fprintf( stdout, "\nMessage received: %s",msg);

	return 0;
}
