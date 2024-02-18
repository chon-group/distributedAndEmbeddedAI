#ifndef __JAVINO_H__

#define __JAVINO_H__

#include <stdio.h>

#define JAVINO_HEADER_LEN 6

void javino_init(int port);

int avaliable_msg();

char* javino_get_msg();

int javino_send_msg(int port, const char* msg_to_send);

#endif