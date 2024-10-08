#ifndef WRLOCK_H
#define WRLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

extern int read;
extern int write;
extern int q_write;

extern pthread_mutex_t mutex;
extern pthread_cond_t cond_read;
extern pthread_cond_t cond_write;

void init_read();

void finish_read();

void init_write();

void finish_write();

#endif








