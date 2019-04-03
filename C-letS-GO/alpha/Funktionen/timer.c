
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


static void *timerFunc(void* var);

volatile int stop = 0;

void update();

int initTimer(){

	int res;
	pthread_t timerThread;
	res = pthread_create(&timerThread, NULL, &timerFunc, NULL);

	if(res != 0){
		printf("Thread Fehler");
		return -1;
	}

	
	return 0;

} 



static void *timerFunc(void* val){

	while(1){
		if(stop){
			break;
		}	
	
		update();

		usleep(500000);
	}
	
}


void update(){
	
}
