#include <javino.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

char* recv_buffer;

pthread_mutex_t mutex;

pthread_t thread_id;

int in;
int out;
int size;

int exogenous_port;

// Returns a message string
// Returns NULL on error

void* main_loop(void *port)
{
    char buffer[ 7 ];

	int local_port = *( (int*)port );
	
	char msg_size_str[5];
	
	long int msg_size;

	int nbytes_read;

	while (1) {
	
		nbytes_read = read( local_port , 
			buffer,  
			sizeof(char) * 6) ;
							
		if ( nbytes_read != (long int)(6*sizeof(char)) ){
			fprintf(stderr, "\nError! Couldn't get message header!");

			return NULL;

		}

#ifdef __EXTRA_DEBUG_MESSAGES__				
	else {

		fprintf(stderr, 
			"\n(main_loop) Message header: %s", 
			buffer);
	}
#endif	
		
		msg_size_str[0] = '0';		
		msg_size_str[1] = 'x';
		msg_size_str[2] = buffer[4];
		msg_size_str[3] = buffer[5];
		msg_size_str[4] = '\0';

#ifdef __EXTRA_DEBUG_MESSAGES__						
		fprintf(stderr, 
			"\n(main_loop) Message size (string): %s", 
			msg_size_str);
#endif		
		
		msg_size = strtol(msg_size_str,
			NULL,
			0);

#ifdef __EXTRA_DEBUG_MESSAGES__						
		fprintf(stderr, 
			"\n(main_loop) Message size (int): %ld\n", 
			msg_size);
#endif
			
		char *msg = (char*)malloc(
			sizeof(char)* (msg_size + 10) );

		nbytes_read = read( local_port, 
			msg, 
			sizeof(char) * ( msg_size ) );
			
		msg[ msg_size ] = '\0';

#ifdef __EXTRA_DEBUG_MESSAGES__						
		fprintf(stderr, 
			"\n(main_loop) Message received: %s\n", 
			msg);
#endif		


		pthread_mutex_lock( &mutex );		
						
		if ( (long unsigned)nbytes_read != msg_size*sizeof(char) ){

			fprintf(stderr, 
				"\n(main_loop) Error: Expected %lu bytes read, got %lu",
				msg_size*sizeof(char),
				(long unsigned)nbytes_read );

			free( msg );

			recv_buffer = NULL;

		} else {

			if (recv_buffer != NULL){
				free(recv_buffer);
			}

			recv_buffer = msg;
		}

		pthread_mutex_unlock( &mutex );		


#ifdef __DEBUG__							
		fprintf(stderr,
			"\n(main_loop) Message received: %s", 
			msg);
#endif
	}			
	
}

void javino_init(int port){

	pthread_mutex_init( &mutex, NULL);

	exogenous_port = port;

	pthread_create( &thread_id,
		NULL,
		main_loop,
		(void*)&exogenous_port);

}


char* javino_get_msg(){

	char *msg_ptr;

	pthread_mutex_lock( &mutex );

	if ( recv_buffer != NULL ){

		msg_ptr = recv_buffer;

		recv_buffer = NULL;
		
	} else {

		msg_ptr = NULL;

	}

	pthread_mutex_unlock( &mutex );

	return msg_ptr;
}


int javino_send_msg(int port, const char* msg_to_send)
{		

	//FILE* fd = fopen(port, "w");	
#ifdef __EXTRA_DEBUG_MESSAGES__		
	fprintf(stderr, 
        "\n(javino_send_msg) Message to send: %s", 
		msg_to_send);
#endif

	int msg_size = strlen( msg_to_send );

#ifdef __EXTRA_DEBUG_MESSAGES__		
	fprintf(stderr, 
        "\n(javino_send_msg) Message size: %d", 
		msg_size);
#endif	

	char *msg = (char*) malloc( 
        sizeof(char) * ( msg_size + 1 ) );
		
	char hex_str[ 5 ];
		
	sprintf( hex_str, "%x", msg_size);
		
	if ( msg_size < 16 ){
		hex_str[ 1 ] = hex_str[ 0 ];
		hex_str[ 0 ] = '0';
	}		


#ifdef __EXTRA_DEBUG_MESSAGES__
	fprintf(stderr, 
		"\nmsg_size (hex): %s",
		hex_str);
	fflush(stderr);
#endif		
			
    msg[ 0 ] = 'f';
    msg[ 1 ] = 'f';
    msg[ 2 ] = 'f';
    msg[ 3 ] = 'e';
    msg[ 4 ] = hex_str[ 0 ];		
    msg[ 5 ] = hex_str[ 1 ];
		
	int i;
	for ( i = 0; i < msg_size; i++){

		msg[ 6 + i ] = msg_to_send[ i ];
		
	}
		
	msg[ 6 + i ] = '\0';
		
#ifdef __DEBUG__		
	fprintf(stderr, 
        "\n(javino_send_message) Javino message to send: %s",
		msg);
#endif		
			
	int nbytes_written = write( port , 
		msg,         
        (msg_size + 6) * sizeof(char) );
    								
	free( msg );

	//fclose( fd );
 
    return nbytes_written;
}


int avaliable_msg(){

	int has_data = 0;


	pthread_mutex_lock( &mutex );

	if ( recv_buffer != NULL ){

		has_data = 1;

	}

	pthread_mutex_unlock( &mutex );

	return has_data;	

}