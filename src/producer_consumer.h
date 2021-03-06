/*
 * Filename: producer_consumer.h
 * Author: Bryan Martin & Joe Listro
 * Class: CSI-385-02
 * Assignment: Lab 2
 * 
 * Date-Assigned: 9/29/2016
 * Due-Date: 9/5/2016
 * 
 * Description: The header file of the producer_consumer program. Contains global variables[:(] and function definitions.
 * 
 * Certification of Authenticity: I certify that this assignment is entirely my own work.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

pthread_mutex_t mutex;
pthread_cond_t readyToProduce, readyToConsume;

int count = 0, *sharedBuffer, bufferSize;

void waitTime(unsigned int seconds);


