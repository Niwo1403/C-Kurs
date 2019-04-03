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

//map mit Infos...
struct map
{
	int hoehe, breite;
	uint16_t vg, hg;
	int spawnAx, spawnAy;
	int spawnBx, spawnBy;
	char *ptr;
};
// GLOBALE VARIABLEN
static struct map *map_ptr;

// FUNKTIONEN
void show_anim();
int startmenu(void);
int createTermbox();
void move(key *figur, uint16_t direction);
void read_map(struct map *, char *);
uint16_t hex_to_int(char);
char getc_arr(int, int);



// MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN
int main(void){
	// Animation
	// show_anim();
	// sleep(1);
	// Startmenue
	int start = startmenu();
	if (start == 1){
		int local = localmenu();
		switch (local)
		{
			case 1:
				return(0);
				break;
		
			case 2:
				//Funktion, um mit 2 Spielern zu spielen
				break;

			case 3:
				//Funktion, um mit 3 Spielern zu spielen
				break;

			case 4:
				//Funktion, um mit 4 Spielern zu spielen
				break;
				
			default:
				break;
		}
		return(0);
	}
	if (start == 3){
		show_anim();
		return(0);
	}
	// Map erstellen
	map_ptr = malloc(sizeof (struct map));
	read_map(map_ptr, "./Maps/Map1.txt");

	// Hauptprogramm,
	// res speichert den eigentlichen return-Wert
	int res = createTermbox();
	
	return(res);
}


//returns the char at (x, y)
char getc_arr(int x, int y){
	int zs = x * (map_ptr->breite) + y;
	(map_ptr->ptr) += zs;
	char c = *(map_ptr->ptr);
	(map_ptr->ptr) -= zs;

	return c;
}

// FUNKTIONEN-INITIALISIERUNG
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
    printf("\t- press [3] to quit the game\n");
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
			default:
				break;
			}
	}
	return(0);
}

int localmenu(void){
	printf("local multiplayer\n");
	printf("\t- press [1] to quit the game\n");
	printf("\t- press [2] to play with 2 players\n");
	printf("\t- press [3] to play with 3 players\n");
	printf("\t- press [4] to play with 4 players\n");

	while(1){
		char l = getchar();
		switch (l)
		{
			case '1':
				return(1);

			case '2':
				printf("2 players\n");
				return(2);

			case '3':
				printf("3 players\n");
				return(3);

			case '4':
				printf("4 players\n");
				return(4);
			default:
				break;
		}
	}
	return(0);
}




int createTermbox(){
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

	// Map wird gezeichnet
	for(int i = 0; i < map_ptr->hoehe; i++)			// y-Koordinate
		for(int j = 0; j < map_ptr->breite; j++){		// x-Koordinate
			tb_change_cell(j, i, *(map_ptr->ptr), map_ptr->vg, map_ptr->hg);
			(map_ptr->ptr)++;						// position Pointer erhoehen
	}


    tb_present();

    // wartet kurz
	sleep(2);
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
	sleep(1);

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
}

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

uint16_t hex_to_int(char c){
	uint16_t ret = 0;
	if (c >= '0' && c <= '9'){
		ret = (uint16_t) c - '0';
	}else if(c >= 'a' && c <= 'f'){
		ret = c - 'a' + 10;
	}else if(c >= 'A' && c <= 'F'){
		ret = c - 'A' + 10;
	}
	return ret;
}

void read_map(struct map *ptr, char *str){
	FILE *file = fopen(str, "r");
	char c = getc(file);
	//Höhe:
	ptr->hoehe = 0;
	while (c != ','){
		ptr->hoehe *= 10;
		ptr->hoehe += c-'0';
		c = getc(file);
	}
	c = getc(file);//für ' '

	//Breite:
	c = getc(file);//erste Zahl
	ptr->breite = 0;
	while (c != ','){
		ptr->breite *= 10;
		ptr->breite += c-'0';
		c = getc(file);
	}
	c = getc(file);//für ' '

	//Hintergrund:
	c = getc(file);//erste Zahl
	ptr->hg = 0;
	while (c != ','){
		ptr->hg *= 16;
		ptr->hg += hex_to_int(c);
		c = getc(file);
	}
	c = getc(file);//für ' '

	//Vordergrund
	c = getc(file);//erste Zahl
	ptr->vg = 0;
	while (c != '\n'){
		ptr->vg *= 16;
		ptr->vg += hex_to_int(c);
		c = getc(file);
	}

	//Spawns von A:
	c = getc(file);//erste Zahl
	ptr->spawnAx = 0;
	while (c != ','){
		ptr->spawnAx *= 10;
		ptr->spawnAx += c-'0';
		c = getc(file);
	}
	c = getc(file);//für ' '
	c = getc(file);//erste Zahl von y koord.
	ptr->spawnAy = 0;
	while (c != ','){
		ptr->spawnAy *= 10;
		ptr->spawnAy += c-'0';
		c = getc(file);
	}
	c = getc(file);//für ' '

	//Spawns von B:
	c = getc(file);//erste Zahl
	ptr->spawnBx = 0;
	while (c != ','){
		ptr->spawnBx *= 10;
		ptr->spawnBx += c-'0';
		c = getc(file);
	}
	c = getc(file);//für ' '
	c = getc(file);//erste Zahl von y koord.
	ptr->spawnBy = 0;
	while (c != '\n'){
		ptr->spawnBy *= 10;
		ptr->spawnBy += c-'0';
		c = getc(file);
	}

	//Char Array b hier:
	int elm = ptr->hoehe * ptr->breite;
	ptr->ptr = malloc(elm);
	for (int i = 0; i < ptr->hoehe; i++){
		c = getc(file);
		for (int j = 0; j < ptr->breite; j++){
			*(ptr->ptr) = c;
			(ptr->ptr)++;
			c = getc(file);
		}
		while (c != '\n'){
			c = getc(file);
		}
	}
	(ptr->ptr) -= elm;

	fclose(file);
}

//fertige Funktionen:

void show_anim() {
	system("clear");
	puts(
"+-----------------------------------------------------------------+\n\
|   #######         ##                       ##        #######    |\n\
| ###    ###        ##          #####        ##       #########   |\n\
| ##                ##       ####    ###   ######      ###        |\n\
| ##          ####  ##      ##      ###      ##         ####      |\n\
| ##                ##      ########         ##           ####    |\n\
| ###    ###        ####    ##       ##      ##        ########   |\n\
|   #######         #####    #########       ###      ########    |\n\
|=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=|");
	usleep(500000);
	const char ptr[17][68] = { 
	 "|       #################                   ###########           |",
	 "|   #######################            #####################      |",
	 "|  #########################         #########################    |",
	 "| #########          ########       #######             ########  |", 
	 "| ######              #######      ######                 ######  |",
	 "| ######                           ######                 ######  |", 
	 "| ######                           ######                 ######  |", 
	 "| ######                           ######                 ######  |", 
	 "| ######                           ######                 ######  |", 
	 "| ######                           ######                 ######  |", 
	 "| ######               #######     ######                 ######  |", 
	 "| #######             ########     ######                 ######  |",
	 "| ########            ########      #######            ########   |",
	 "|  ####################### ###       #########################    |",
	 "|   ###################### ###         #####################      |",
	 "|      #################                    ###########           |",
	 "+-----------------------------------------------------------------+"};
	for (int i = 0; i < 17; i++) {
		puts(ptr[i]);
		usleep(100000);
	}
	puts("\n");
}
