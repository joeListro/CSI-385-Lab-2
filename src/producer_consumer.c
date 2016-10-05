/*
 * Filename: producer_consumer.c
 * Author: Bryan Martin and Joe Listro
 * Class: CSI-385-02
 * Assignment: Lab 2
 * 
 * DateAssigned: 9/29/2016
 * DueDate: 9/4/2016
 * 	
 * 	Description: A brief description of the purpose of the program.
 *
 * 	Certification of Authenticity: I certify that this assignment is entirely my own work.
 *
 */

#include "producer_consumer.h"

#define MAX_THREADS 1000000000  // Max number of elements allowed on thread.
pthread_mutex_t PTHREAD_MUTEX_INITALIZER;
pthread_cond_t cond1, cond2;

int *sharedBuffer[];
int numProducers = 0, numConsumers = 0, bufferSize = 0, count = 0;

void waitTime(unsigned int seconds) {
	unsigned int finishTime = time(0) + seconds;
	while(time(0) < finishTime);
}

void *producerMain(unsigned int numExistingProducers){
	String pID = "p" + numExistingProducers;
	waitTime(1);	
	srand(time(NULL));
	int numElements = rand() % bufferSize;
 	for(int i = 0; i < numElements; i++) {
		count = count + 1;
		printf("%i : %i has been added to the thread.", pID, count);
	}
}

void &consumerMain(unsigned int numExistingConsumers){
	String cID = "c" + numExistingConsumers;
	waitTime(1);
	int removedItem;
	printf("%i : %i has been removed from the thread.", cID, removedItem);
}

int main(int argc, char * argv[]){
	if(argc < 4){
		printf("Too few arguments.\n");
		return(1);
	} else if (argc > 4){
		printf("Too many arguments.\n");
		return(1);
	}
	else {
		numProducers = atoi(argv[1]);
		numConsumers = atoi(argv[2]);
		bufferSize = atoi(argv[3]);
	}
	printf("ARGUMENTS - P:%i C:%i BS:%i\n", numProducers, numConsumers, bufferSize);

	sharedBuffer = new [bufferSize];

}
