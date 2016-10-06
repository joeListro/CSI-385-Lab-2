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

pthread_mutex_t mutex;
pthread_cond_t pCond, cCond;

int count = 0, *sharedBuffer, bufferSize;

void waitTime(unsigned int seconds) {
	unsigned int finishTime = time(0) + seconds;
	while(time(0) < finishTime);
}

void *producerMain(void *numExisting){
	int id = *( int* ) numExisting;
	waitTime(1);	
	int i, numElements = rand() % bufferSize;
 	for(i = 0; i < numElements; i++) {
		count = count + 1;
		printf("%i : %i has been added to the thread.", id, count);
	}
}

void *consumerMain(void *numExisting){
	int id = *( int* ) numExisting;
	waitTime(1);
	int removedItem;
	printf("%i : %i has been removed from the thread.", id, removedItem);

}

int main(int argc, char* argv[]){
	int numProducers, numConsumers;
	pthread_t *prod, *con;

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

	printf("ARGUMENTS - Producers: %i\nConsumers:%i\nBufferSize:%i\n", numProducers, numConsumers, bufferSize);

	sharedBuffer = malloc(sizeof(*sharedBuffer) * bufferSize);

	prod = (pthread_t *)malloc(numProducers * sizeof(pthread_t));
	con = (pthread_t *)malloc(numConsumers * sizeof(pthread_t));

	int i;
	for(i=0; i<numProducers; i++){
		pthread_create(&prod[i],NULL,producerMain,NULL);
	}
	
	for(i=0; i<numConsumers; i++){
		pthread_create(&con[i],NULL,consumerMain,NULL);
	}

	printf("Press q to kill all threads");
	
	free(sharedBuffer);
	free(prod);
	free(con);
}
