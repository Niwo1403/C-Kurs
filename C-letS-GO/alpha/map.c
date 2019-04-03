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


// STRUCTS
//map mit Infos...
struct map
{
	int hoehe, breite;
	uint16_t vg, hg;
	int spawnAx, spawnAy;
	int spawnBx, spawnBy;
	char *ptr;
};

// ein 'Pixel'
typedef struct{
	int x;
	int y;
	unsigned char ch;
}key;	


typedef struct{
	int x;				// Position auf der map
	int y;
	char ch;
	int bombs;			// Anzahl der Bomben im Inventar
	int isDead;			// ob der Spieler noch lebt
	int isActive;		// ob der Spieler am Spiel teilnimmt bzw. existiert
}player;
// GLOBALE VARIABLEN
static struct map *map_ptr;
int zustand = 0;

enum Direction {STAND, UP, DOWN, LEFT, RIGHT};

// FUNKTIONEN
void show_anim();
int startmenu(void);
int createTermbox();
void move(player *figur, uint16_t direction);
void read_map(struct map *, char *);
uint16_t hex_to_int(char);
char getc_arr(int, int);
void show_endanim();
int check(enum Direction, int, int);
void tick();

//git config credential.helper store
//git push https://github.com/Niwo1493/C-Kurs.git

// MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN
int main(void){
	// Animation
	show_anim();
	// Startmenue
	zustand = startmenu();

	if (zustand == 1){
		//Funktion, um Spiel zu starten
	}

	if (zustand == 2){
		//Funktion, um online Multiplayer zu starten
	}

	if (zustand == 3){
		printf("How to play\n");
		printf("\t- player 1 moves with [W], [A], [S], [D] and places bombs with [Enter]\n");
		printf("\t- player 2 moves with [ARROW_UP], [ARROW_LEFT], [ARROW-DOWN], [ARROW_RIGHT] and places bombs with [Space]\n");
		printf(" \n");
		printf("Bombs can't destroy the solid blocks (#)\n");
	}

	if (zustand == 4){
		show_endanim();
		return(0);
	}

	// Map erstellen
	map_ptr = malloc(sizeof (struct map));
	read_map(map_ptr, "./Maps/Map1.txt");

	//Thread (Ticks) erstellen
	pthread_t timerThread;
	int res = pthread_create(&timerThread, NULL, &tick, NULL);
	if(res != 0){
		printf("Thread Fehler");
		return -1;
	}

	// Hauptprogramm,
	// res speichert den eigentlichen return-Wert
	int res = createTermbox();
	
	pthread_exit(timerThread);//Thread beenden
	return(res);
}


void tick(){
	while (zustand != 4){

	}
	return 0;
}

//returns the char at (x, y)
char getc_arr(int x, int y){
	int zs = x * (map_ptr->breite) + y;
	(map_ptr->ptr) += zs;
	char c = *(map_ptr->ptr);
	(map_ptr->ptr) -= zs;

	return c;
}

int check(enum Direction direct, int x, int y){
    switch (direct){
        case UP:
            y++;
            break;
        case DOWN:
            y--;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }
    char c = getc_arr(x, y);
    if (c == '+' || c == '-' || c == '|'){//Disjunktion von allen nicht durchlässigen Blöcken
        return 1;
    }
    return 0;
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
	player *player1 = malloc(sizeof(player));
	player1->x = 10;
	player1->y = 10;
	player1->ch = '@';
	player1->bombs = 3;
	player1->isDead = 0;
	player1->isActive = 0;
	// Figur auf Termbox registrieren
	tb_change_cell(player1->x, player1->y, player1->ch, map_ptr->vg,map_ptr->hg);

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
				move(player1, ev.key);
				break;

			// Sonst passiert nix
			default:
				break;
		}
	}
	// schließt Termbox
	tb_shutdown();
}

void move(player *figur, uint16_t direction){
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
	char clets[9][68] = {
	"+-----------------------------------------------------------------+",
	"|   #######         ##                       ##        #######    |",
	"| ###    ###        ##          #####        ##       #########   |",
	"| ##                ##       ####    ###   ######      ###        |",
	"| ##          ####  ##      ##      ###      ##         ####      |",
	"| ##                ##      ########         ##           ####    |",
	"| ###    ###        ####    ##       ##      ##        ########   |",
	"|   #######         #####    #########       ###      ########    |",
	"|=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=|"};
	for (int i = 0; i < 9; i++){
		puts(clets[i]);
	}
	usleep(200000);
	const char ptr[17][68] = { 
	 "|       #################                   ###########           |",
	 "|   #######################            #####################      |",
	 "|  #########################         #########################    |",
	 "| #########          ########       #######             #######   |", 
	 "| ######              #######      ######                 ######  |",
	 "| ######                           ######                 ######  |", 
	 "| ######                           ######                 ######  |", 
	 "| ######                           ######                 ######  |", 
	 "| ######                           ######                 ######  |", 
	 "| ######               #######     ######                 ######  |", 
	 "| ######               #######     ######                 ######  |", 
	 "| #######             ########     ######                 ######  |",
	 "| ########            ########      #######            ########   |",
	 "|  ####################### ###       #########################    |",
	 "|   ###################### ###         #####################      |",
	 "|      #################                    ###########           |",
	 "+-----------------------------------------------------------------+"};
	for (int i = 0; i < 17; i++) {
		puts(ptr[i]);
		usleep(15000);
	}
	puts("");
}

void show_endanim(){
	system("clear");
	const char ptr[26][146+1] = { 
	"+-----------------------------------------------------------------+-------------------------------------------------------------------------------",
	"|   #######         ##                       ##        #######    |                                                                               ",
	"| ###    ###        ##          #####        ##       #########   |   ##################      #####                 #####   ####################  ",
	"| ##                ##       ####    ###   ######      ###        |  ######################    #####               #####    ####################  ",
	"| ##          ####  ##      ##      ###      ##         ####      |  #######################    #####             #####     ####################  ",
	"| ##                ##      ########         ##           ####    |  ######          #######     #####           #####      #####                 ",
	"| ###    ###        ####    ##       ##      ##        ########   |  #####            ######      #####         #####       #####                 ",
	"|   #######         #####    #########       ###      ########    |  #####            ######       #####       #####        #####                 ",
	"|=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=|  #####           ######         #####     #####         #####                 ",
	"|       #################                   ###########           |  #####         ######            #####   #####          #####                 ",
	"|   #######################            #####################      |  ######      #######              ##### #####           #####                 ",
	"|  #########################         #########################    |  ##################                #########            ####################  ",
	"| #########          ########       #######             #######   |  ####################               #######             ####################  ", 
	"| ######              #######      ######                 ######  |  ######################              #####              ####################  ",
	"| ######                           ######                 ######  |  ######         ########             #####              #####                 ", 
	"| ######                           ######                 ######  |  #####            #######            #####              #####                 ", 
	"| ######                           ######                 ######  |  #####             #######           #####              #####                 ", 
	"| ######                           ######                 ######  |  #####             #######           #####              #####                 ", 
	"| ######               #######     ######                 ######  |  #####             #######           #####              #####                 ", 
	"| ######               #######     ######                 ######  |  #####            #######            #####              #####                 ", 
	"| #######             ########     ######                 ######  |  ######         ########             #####              #####                 ",
	"| ########            ########      #######            ########   |  ######################              #####              ##################### ",
	"|  ####################### ###       #########################    |  ####################                #####              ##################### ",
	"|   ###################### ###         #####################      |   ################                   #####              ##################### ",
	"|      #################                    ###########           |                                                                               ", 
	"+-----------------------------------------------------------------+-------------------------------------------------------------------------------"};
	for (int i = 67; i < 146; i++){
		usleep(10000);
		system("clear");
		for (int j = 0; j < 26; j++){
			char *tmp = malloc(i+1+6);
			strncpy(tmp, ptr[j], i);
			printf("%s", tmp);
			if (j == 0 || j == 25){
				puts("--+");
			}else{
				puts("  |");
			}
			free(tmp);
		}
	}

}