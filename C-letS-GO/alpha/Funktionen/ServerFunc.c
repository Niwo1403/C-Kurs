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
#define MAX_CLIENTS 3


static void *serverReciveFunc(void* val);
int initServer();
void sendMessage(char *msg);
void reciveMessage(char *msg, int clientID);


static volatile int client_socket[4];
pthread_t serverRecThread;

int main(int argc, char **argv){
	int res;
	char msg[30];
	res = initServer();

	if(res != 0) return 1;


	while(1){
		scanf("%s", &msg);
		if(strcmp(msg, "exit") == 0){
			printf("Exit\n");
			pthread_cancel(serverRecThread);
			return 0;
		}
		
		sendMessage(msg);
	}

	return 0;
}


int initServer(){
	int i;
	for (i = 0; i < MAX_CLIENTS; i++){   
        client_socket[i] = 0;   
    }

	int res;
	res = pthread_create(&serverRecThread, NULL, &serverReciveFunc, NULL);
	if(res != 0){
		printf("Thread Fehler\n");
		return -1;
	}

	
	return 0;
} 





static void *serverReciveFunc(void* val){
	int counter = 0;
	int max_sd, sd, activity, new_socket, i, valread;
	
	fd_set readfds;
	char buffer[1025];
	char msg[] = "abc";

	struct sockaddr_in dest;
	struct sockaddr_in serv;

	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	int mysocket;

	
	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&serv, 0, sizeof(serv));

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORTNUM);



	mysocket = socket(AF_INET, SOCK_STREAM, 0);

	bind(mysocket, (struct sockaddr *)&serv, sizeof (struct sockaddr));

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
			
			(new_socket = accept(mysocket, (struct sockaddr *)&dest, &socksize));
			//Fehlerbehandlung

			printf("New Connection\n");
			
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
					//User disconected
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



void sendMessage(char *msg){
	int sd, i;
	for(i = 0; i<MAX_CLIENTS; i++){
		sd = client_socket[i];
		send(sd, msg, strlen(msg), 0);
	}
}


void reciveMessage(char *msg, int ClientID){
	//was soll mit emfangenen Nachrichten passieren?
	printf("%s\n", msg);
					
}
 
