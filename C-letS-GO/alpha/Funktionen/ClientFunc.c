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

int initClient();
void *clientReciveFunc(void* val);
void sendMessage(char *msg);
void reciveMessage(char *msg);

volatile int mysocket;

pthread_t clientRecThread;

int main(int argc, char **argv){
	int res;
	char msg[30];
	
	res = initClient(argv[1]);

	while(1){
		scanf("%s", &msg);


		if(strcmp(msg, "exit") == 0){
			printf("Exit\n");
			pthread_cancel(clientRecThread);
			return 0;
		}

		sendMessage(msg);
	}

	return 0;
}

int initClient(char *ip){
	int res;
	res = pthread_create(&clientRecThread, NULL, &clientReciveFunc, ip);

	if(res != 0){
		printf("Thread Fehler");
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
	//dest.sin_addr.s_addr = inet_addr(val);
	dest.sin_addr.s_addr = inet_addr(val);
	//dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	dest.sin_port = htons(PORTNUM);

	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));


	while(1){
		
		len = read(mysocket, buffer, MAXRCVLEN);
		if(len > 0){
			buffer[len] = '\0';

			reciveMessage(buffer);
			//printf("Recived %s (%d bytes).\n", buffer, len);
		}
		usleep(500000);
	}


}


void sendMessage(char *msg){
	send(mysocket, msg, strlen(msg), 0);
}


void reciveMessage(char *msg){
	//was soll passieren, wenn man eine nachricht empfängt
	printf("%s\n", msg);

}




