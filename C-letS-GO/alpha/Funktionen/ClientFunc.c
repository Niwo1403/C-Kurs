#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#define MAXRCVLEN 500
#define PORTNUM 2300

int initClient(char *ip);
int closeClient();
void *clientReciveFunc(void* val);
void sendMessageC(char *msg);
void reciveMessage(char *msg);

volatile int mysocket;
volatile pthread_t clientRecThread;


//start mit initClient(char *ip)
//
//message senden mit sendMessageC(char *msg)
//
//reciveMessage(char *msg) füllen mit reaktion zu erhaltenen nachrichten
//
//ende mit closeClient()



int initClient(char *ip){
	int res;
	res = pthread_create(&clientRecThread, NULL, &clientReciveFunc, ip);

	if(res != 0){
		//FIXME exit with error
		return -1;
	}
	
	return 0;
}

int closeClient(){

	int res = close(mysocket);
	if(res != 0){
		//FIXME exit with error
		return -1;
	}
		
	res = pthread_cancel(clientRecThread);
	if(res != 0){
		//FIXME exit with error
		return -1;
	}

	return 0;
}   


void *clientReciveFunc(void* val){
	int len;
	char buffer[MAXRCVLEN+1];
	struct sockaddr_in dest;

	mysocket = socket(AF_INET, SOCK_STREAM, 0);

	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(val);
	dest.sin_port = htons(PORTNUM);

	int res = connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));

	if(res != 0){
		//FIXME exit with error
		closeClient();
		return NULL;
	}

	while(1){
		
		len = read(mysocket, buffer, MAXRCVLEN);
		if(len > 0){
			buffer[len] = '\0';
			reciveMessage(buffer);
		}
		usleep(500000);
	}


}


void sendMessageC(char *msg){
	send(mysocket, msg, strlen(msg), 0);
}


void reciveMessageC(char *msg){
	//was soll passieren, wenn man eine nachricht empfängt

}

