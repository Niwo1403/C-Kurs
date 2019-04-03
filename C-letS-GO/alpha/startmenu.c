#include <stdio.h>
#include <stdlib.h>

int startmenu(void);

int main (void){
    startmenu();
    return(0);
}

int startmenu(void){
	//Optionen im Startmenü:

	//Local Multiplayer
		//2 players
		//3 players
		//4 players
	//Online Multiplayer
		//Host Game
		//Join Game

	printf("Welcome!\n");
	printf("\t- press [1] to play local multiplayer\n");
    printf("\t- press [2] to play online multiplayer\n"); 
	printf("\t- press [3] to learn how to play the game\n");
    printf("\t- press [4] to quit the game\n");
	printf("> ");
	// int menubufferlength = 5;
	// char menubuffer[10];
	// fgets(menubuffer, menubufferlength, stdin);

	while(1){
		char c = getchar();
		switch(c){
			case '1':
				printf("local multiplayer\n");
				return 1;
			case '2':
				printf("online multiplayer\n");
				return 2;
			case '3':
				return 3;

			case '4':
				return 4;
			default:
				break;
			}
	}
	return(0);
}
