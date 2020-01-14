#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mpi.h"
#define MSG_EXIT 1
#define MSG_SEND 2
#define MSG_TIME 3
#define MSG_COUNT 4

void base_station(char* c_time, time_t what_time);

void  encrypt_decrypt(int inp[],size_t len);