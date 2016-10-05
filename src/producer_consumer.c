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

pthread_mutex_t MUTEX;
pthread_cond_t pCond, cCond;

int count = 0;

void waitTime(unsigned int seconds) {
	unsigned int finishTime = time(0) + seconds;
	while(time(0) < finishTime);
}

void producerMain(unsigned int numExisting, int bufferSize){
	char* pID = "p" + getsid();
	waitTime(1);	
	int i, numElements = rand() % bufferSize;
 	for(i = 0; i < numElements; i++) {
		count = count + 1;
		printf("%i : %i has been added to the thread.", pID, count);
	}
}

void consumerMain(unsigned int numExisting){
	char* cID = "c" + getsid();
	waitTime(1);
	int removedItem;
	printf("%i : %i has been removed from the thread.", cID, removedItem);
}

int main(int argc, char* argv[]){
	int *sharedBuffer;
	int numProducers, numConsumers, bufferSize;

	srand(time(NULL));

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

	sharedBuffer = malloc(sizeof(*sharedBuffer) * bufferSize);

}
