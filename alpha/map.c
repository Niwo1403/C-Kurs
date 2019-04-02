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


// FUNKTIONEN
void move(key *figur, uint16_t direction);




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

	// wieder auf Konsolo
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

