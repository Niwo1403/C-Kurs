#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORTNUM 2300 
#define MAX_CLIENTS 3

int initServer();
int closeServer();
void *serverReciveFunc(void* val);
void sendMessageS(char *msg);
void reciveMessageS(char *msg, int clientID);

volatile int mysocket;
volatile int client_socket[4];
volatile pthread_t serverRecThread;

//start mit initServer()
//
//message senden mit sendMessageS(char *msg)
//
//reciveMessageS(char *msg) füllen mit reaktion zu erhaltenen nachrichten
//
//ende mit closeClient()

int initServer(){
	int i;
	for (i = 0; i < MAX_CLIENTS; i++){   
        client_socket[i] = 0;   
    }

	int res;
	res = pthread_create(&serverRecThread, NULL, &serverReciveFunc, NULL);
	if(res != 0){
		//FIXME exit with error
		return -1;
	}

	return 0;
} 

int closeServer(){
	int ret = 0;
	int res;
	for(int i = 0; i< MAX_CLIENTS; i++){
		if(client_socket[i] != 0){
			res = close(client_socket[i]);
			if(res != 0){
				//FIXME exit with error
				ret = -1;
			}
		}
	}

	res = close(mysocket);
	if(res != 0){
		//FIXME exit with error
		ret = -1;
	}
		
	res = pthread_cancel(serverRecThread);
	if(res != 0){
		//FIXME exit with error
		ret = -1;
	}

	return ret;
} 



void *serverReciveFunc(void* val){
	int res, max_sd, sd, activity, new_socket, i, valread;
	
	fd_set readfds;
	char buffer[1025];

	struct sockaddr_in dest;
	struct sockaddr_in serv;

	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	
	socklen_t socksize = sizeof(struct sockaddr_in);
	memset(&serv, 0, sizeof(serv));

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORTNUM);



	mysocket = socket(AF_INET, SOCK_STREAM, 0);
	if(mysocket = -1){
		//FIXME exit with error	
	}

	res = bind(mysocket, (struct sockaddr *)&serv, sizeof (struct sockaddr));
	if(res != 0){
		//FIXME exit with error
	}

	listen(mysocket, 2);

	
	while(1){

		FD_ZERO(&readfds);

		FD_SET(mysocket, &readfds);
	
		max_sd = mysocket;
		
		for(i=0;i<MAX_CLIENTS;i++){
			sd = client_socket[i];			
			
			if(sd > 0){
				FD_SET(sd, &readfds);
			}

			if(sd > max_sd) max_sd = sd;
					
		}

		activity = select(max_sd + 1, &readfds, NULL, NULL, &tv);

		if(FD_ISSET(mysocket, &readfds)){
			
			if((new_socket = accept(mysocket, (struct sockaddr *)&dest, &socksize))<0){
				//FIXME exit with error
			}
			

			for(i = 0; i<MAX_CLIENTS; i++){
				if(client_socket[i] == 0){
					client_socket[i] = new_socket;
					break;
				}
			}
			
		}

		for(i = 0; i<MAX_CLIENTS; i++){
			sd = client_socket[i];

			if(FD_ISSET(sd, &readfds)){
				if((valread = read(sd, buffer, 1024)) == 0){
					userDisconnect(sd)
					close(sd);
					client_socket[i] = 0;
				}else{
					buffer[valread] = '\0';
					reciveMessage(buffer, sd);
				}
			}
		}
	}
}



void sendMessageS(char *msg){
	int sd, i;
	for(i = 0; i<MAX_CLIENTS; i++){
		sd = client_socket[i];
		send(sd, msg, strlen(msg), 0);
		//eventuell Fehlerbehandlung
	}
}


void reciveMessageS(char *msg, int ClientID){
	//was soll mit emfangenen Nachrichten passieren?
					
}

void userDisconnect(int ClientID){
	//was soll beim Disconnect passieren

}
 
