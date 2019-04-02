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
	printf("\t- press 1 to play local multiplayer\n");
    printf("\t- press 2 to play online multiplayer\n"); 
    printf("\t- press 3 to quit the game\n");
	printf("> ");
	int menubufferlength = 5;
	char menubuffer[10];
	fgets(menubuffer, menubufferlength, stdin);
	int option = atoi(menubuffer);
	if(option == 0){
		printf("Keine gültige Eingabe\n");
		startmenu();
	}
	else{
		switch (option)
		{
			case 1:
                printf("local multiplayer\n");
				//Funktion für lokalen Multiplayer
				break;

			case 2:
                printf("online multiplayer\n");
				//Funktion für online Multiplayer
				break;

			case 3:
				return(0);
				break;

			default:
				printf("Keine gültige Eingabe\n ");
				startmenu();
				break;
		}
	}
	return(0);
}