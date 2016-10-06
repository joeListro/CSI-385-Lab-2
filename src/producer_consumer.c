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
pthread_cond_t readyToProduce, readyToConsume;

int count = 0, *sharedBuffer, bufferSize;

void waitTime(unsigned int seconds) {
	unsigned int finishTime = time(0) + seconds;
	while(time(0) < finishTime);
}

void *producerMain(void *numExisting){
	int id = *( int* ) numExisting;
	waitTime(1);

	/* Try to grab the lock */
	pthread_mutex_lock(&mutex);
	
	/* Wait for the lock when the buffer isn't full. */
	while(sizeof(sharedBuffer) < bufferSize){ pthread__cond_wait(&readyToConsume, &mutex); }

	/* Add items to the buffer*/
	int i, numElements = rand() % bufferSize;
 	count = count + numElements;
	for(i = 0; i < numElements; i++) {
		sharedBuffer[count + i] = (count + i)
		printf("%i : %i has been added to the thread.", id, (count + I));
	}

	pthread_cond_signal(&readyToConsume);
	pthread_mutex_unlock(&mutex);
}

void *consumerMain(void *numExisting){
    int id = *( int* ) numExisting;
    int removedItem;
    
    while(true) {
        waitTime(1);
        
        /* Wait for the lock when the buffer isn't empty. */
        while(sizeof(sharedBuffer) > 0){ pthread_cond_wait(&readyToProduce, &mutex); }
            
        sharedBuffer[count] = 0;
        
        count = count - 1;
        
        printf("%i : %i has been removed from the thread.", id, removedItem);
        
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&readyToProduce);
    }
    return;
}

int main(int argc, char* argv[]){
    /* Initialize variables */
	int numProducers, numConsumers;
	pthread_t *prod, *con;

	srand(time(NULL));

    /* Check number of arguments */
	if(argc < 4){
		printf("Too few arguments.\n");
		return(1);
	} else if (argc > 4){
		printf("Too many arguments.\n");
		return(1);
	}
	else {
        /* Read arguments */
		numProducers = atoi(argv[1]);
		numConsumers = atoi(argv[2]);
		bufferSize = atoi(argv[3]);
	}

	printf("ARGUMENTS - Producers: %i\nConsumers:%i\nBufferSize:%i\n", numProducers, numConsumers, bufferSize);

    /* Allocate memory for buffer and producer/consumer threads */
	sharedBuffer = malloc(sizeof(*sharedBuffer) * bufferSize);

	prod = (pthread_t *)malloc(numProducers * sizeof(pthread_t));
	con = (pthread_t *)malloc(numConsumers * sizeof(pthread_t));

    /* Create producer threads */
	int i;
	for(i=0; i<numProducers; i++){
		pthread_create(&prod[i],NULL,producerMain,NULL);
	}
	
    /* Create consumer threads */
	for(i=0; i<numConsumers; i++){
		pthread_create(&con[i],NULL,consumerMain,NULL);
	}

    /* Kill on user input of char q */
	printf("Press q to kill all threads\n");
    
    while(true) {
        /* Wait for the user to press q */
        if(getchar() != 'q') {
            break;
        }
    }
	
    /* Kill all threads */
    for(i=0; i<numProducers; i++){
        pthread_cancel(prod[i]);
    }
    
    for(i=0; i<numConsumers; i++){
        pthread_cancel(con[i]);
    }
    
    /* Join all thread processes back with main */
    for(i=0; i<numProducers; i++){
        pthread_join(prod[i],0);
    }
    
    for(i=0; i<numConsumers; i++){
        pthread_join(con[i],0);
    }
    
	free(sharedBuffer);
	free(prod);
	free(con);
}
