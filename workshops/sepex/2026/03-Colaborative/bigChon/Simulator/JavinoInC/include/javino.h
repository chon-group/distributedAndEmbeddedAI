#ifndef __JAVINO_H__

#define __JAVINO_H__

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define JAVINO_HEADER_LEN 6

/**
 * \brief Initialized internal Javino structures
 * 
 * This must be called before using any Javino primitives
 * 
 * \param port Port to listen and write messages to.
 * It must be already openned by a open() systemc call
 * 
*/
void javino_init(int port);

/**
 * \brief Ends Javino, freeing all internal structures allocated
 * 
 * 
*/
void javino_exit();

/** \brief Checks if there is any Javino messages received
 * 
 * \return 1 if there is, 0 othewrwise
 * 
*/
int javino_avaliable_msg();

/**
 * \brief Returns a pointer to the last message received by the Javino
*/
char* javino_get_msg();

/**
 * \brief Send a message through Javino
 * 
 * \param msg_to_send Pointer to the message
 * 
 * \return number of bytes written on success, -1 on error
*/
int javino_send_msg(const char* msg_to_send);

#endif