/*	tb_change_cell(int koorX, int koorY, char Zeichen, int FarbeZeichen, int FarbeBackGround)
	--> damit manipuliert man Pixel

	tb_present();
	--> aktuallisiert die Termbox für den Anwender

	tb_poll_event()
		--> Wartet auf ein Event (Mouseclick, Keyboard)
*/




#include <stdio.h>
#include <string.h>
#include "termbox.h"
#include <unistd.h>
#include <stdlib.h>



// ein 'Pixel'
typedef struct key{
	int x;
	int y;
	unsigned char ch;
}key;	

// Schablone fuer die Grenzen der Maps
const char boundaryX[] = "##########################################################################";
const char boundaryY[] = "#                                                                        #";

//map mit Infos...
/*struct  map
{
	int hoehe, breite;
	int spawnAx, spawnAy;
	int spawnBx, spawnBy;
	char *ptr;
};*/


// FUNKTIONEN
void move(key *figur, uint16_t direction);
void show_anim();



// MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN
int main(void){

	// MAP-GESTALTUNG
	// MAP-GESTALTUNG
	// MAP-GESTALTUNG
	// MAP-GESTALTUNG
	// MAP-GESTALTUNG

	// Termbox anlegen
	int code = tb_init();
	if (code < 0) {
        fprintf(stderr, "termbox init failed, code: %d\n", code);
        return -1;
    }
    // Input- & OutputModus (viele Farben) der TB festlegen
    tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
    tb_select_output_mode(TB_OUTPUT_256);

    // cleart die TB einmal - macht sie "startklar"
    tb_clear();

     // Erste Zeile  - Horizontale Grenze
    for(unsigned int i = 0; i < strlen(boundaryX); i++)
        tb_change_cell(i, 0, boundaryX[1], 0, 0);

    // 1-te und n-1-te Zeile (vertikal)
    for(unsigned int i = 1; i < 20; i++){
        // horizontal
    	for(unsigned int j = 0; j < strlen(boundaryY); j++)
        	tb_change_cell(j, i, boundaryY[j], 0, 0);
    }
    for(unsigned int i = 0; i < strlen(boundaryX); i++)
        tb_change_cell(i, 20, boundaryX[1], 0, 0);


    //  Zeichnet die Termbox auf Terminal neu
    //	--> zeichnet alle neuen Änderungen
    tb_present();

    // wartet kurz
	sleep(5);
	// neue Manipulation
	tb_change_cell(10, 10, '(',0,0);
	tb_change_cell(11, 10, ' ',0,0);
	tb_change_cell(12, 10, '.',0,0);
	tb_change_cell(13, 10, ' ',0,0);
	tb_change_cell(14, 10, 'Y',0,0);
	tb_change_cell(15, 10, ' ',0,0);
	tb_change_cell(16, 10, '.',0,0);
	tb_change_cell(17, 10, ' ',0,0);
	tb_change_cell(18, 10, ')',0,0);


	// Eine Figur anlegen
	key figur1 = {20,15,'!'};
	// Figur auf Termbox registrieren
	tb_change_cell(figur1.x, figur1.y, figur1.ch, 0,0);




	// Zeichnet neu
	tb_present();
	sleep(3);

	// AB HIER: EVENTS
	// AB HIER: EVENTS
	// AB HIER: EVENTS
	// AB HIER: EVENTS
	// AB HIER: EVENTS



	while(1){
		// Ein Event anlegen
		struct tb_event ev;
		int t = tb_poll_event(&ev);		// Wartet solange, bis irgendeine Eingabe gemacht wird (Tastatur, Maus)

		// Falls Fehler beim Erstellen eines Events, beende
		if(t == -1){
			fprintf(stderr, "Event-Fehler");
			return (-1);
		}
		// Falls Bewegung
		switch(t){

			case 'w':
				tb_shutdown();
				return(0);
				break;

			// Falls  Tastatur-Eingabe
			case TB_EVENT_KEY :
				// Falls ESC: ABBRUCH
				if(ev.key == TB_KEY_ESC){
					tb_shutdown();
					return(0);
				}

				// sonst: Bewegung
				move(&figur1, ev.key);
				break;

			// Sonst passiert nix
			default:
				break;
		}
	}
	// schließt Termbox
	tb_shutdown();

	// wieder auf Konsole
	return(0);
}


// FUNKTIONEN-INITIALISIERUNG
void move(key *figur, uint16_t direction){
	tb_change_cell(figur->x, figur->y, ' ', 0,0);		// "Pixel" wo Figur war, ist nun leer

	// Position der Figur ändern oder Bombe planten
	switch(direction){
		case TB_KEY_ARROW_UP :
				figur->y = figur->y - 1;
				break;
		case TB_KEY_ARROW_DOWN :
				figur->y = figur->y + 1;
				break;
		case TB_KEY_ARROW_RIGHT :
				figur->x = figur->x + 1;
				break;
		case TB_KEY_ARROW_LEFT :
				figur->x = figur->x - 1;
				break;

		// Strg+Enter 		-		Bomben planten
		case TB_KEY_ENTER:
				tb_change_cell(figur->x -1, figur->y, 'x', 0,0);
				break;

		default:
				break;
	}
	tb_change_cell(figur->x, figur->y,figur->ch, 0,0);	// neuen Pixel setzen
	tb_present();
	return;
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
	printf("\tpress 1 to play local multiplayer\n");
    printf("\tpress 2 to play online multiplayer\n"); 
    printf("\tpress 3 to quit the game\n");
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



//fertige Funktionen:

void show_anim() {
	system("clear");
	puts("+-----------------------------------------------------------------+\n|   #######         ##                       ##        #######    |\n| ###    ###        ##          #####        ##       #########   |\n| ##                ##       ####    ###   ######      ###        |\n| ##          ####  ##      ##      ###      ##         ####      |\n| ##                ##      ########         ##           ####    |\n| ###    ###        ####    ##       ##      ##        ########   |\n|   #######         #####    #########       ###      ########    |\n|=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=|");
	usleep(500000);
	const char ptr[17][68] = { "|       #################                   ###########           |", "|   #######################            #####################      |", "|  #########################         #########################    |", "| #########          ########       #######             ########  |", "| ######              #######      ######                 ######  |", "| ######                           ######                 ######  |", "| ######                           ######                 ######  |", "| ######                           ######                 ######  |", "| ######                           ######                 ######  |", "| ######                           ######                 ######  |", "| ######               #######     ######                 ######  |", "| #######             ########     ######                 ######  |", "| ########            ########      #######            ########   |", "|  ####################### ###       #########################    |", "|   ###################### ###         #####################      |", "|      #################                    ###########           |", "+-----------------------------------------------------------------+"};
	for (int i = 0; i < 17; i++) {
		puts(ptr[i]);
		usleep(100000);
	}
	puts("\n");
}

