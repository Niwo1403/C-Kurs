// prueft ob eine Zelle in einer Richtung eine Wand ist
// 0 wenn nein, ansonsten ja
// 'u' -> up
// 'd' -> down
// 'l' -> left
// 'r' -> right
// alles ausserhalb der map wird als solid betrachtet
int directionNonSolid(array, int x, int y, char direction){
	switch(direction)
		case 'u' :
			if (y == 0) {
				return (1)
			} else {
				return(array[x+((y-1)*width)]);
			}
		case 'd' :
			//FIXME ARRAY_YMAX durch Array-Hoehe ersetzen
			if (y == ARRAY_YMAX) {
				return (1)
			} else {
				return(array[x+((y+1)*width)]);
			}
		case 'l' :
			if (x == 0) {
				return (1)
			} else {
				return(array[x-1+(y*width)]);
			}
		case 'r' :
			//FIXME ARRAY_XMAX durch Array-Breite ersetzen
			if (x == ARRAY_XMAX) {
				return (1)
			} else {
				return(array[x+1+(y*width)]);
			}
}

//FIXME
ARRAY[width*height];

// fuer DAMAGE_ARRAY
void decrementMap(int ARRAY[]) {
	for(int i = 0; i < sizeof(ARRAY)/sizeof(ARRAY[0]); i++) {
		ARRAY[i]--;
	}
}

struct player {
	int x;				// Position auf der map
	int y;
	char ch;
	int bombs;			// Anzahl der Bomben im Inventar
	int isDead;			// ob der Spieler noch lebt
	int isActive;		// ob der Spieler am Spiel teilnimmt bzw. existiert
}

struct bomb {
	int x;				// Position auf der map
	int y;
	int radius;			// Explosionsradius
	int timer;			// Wie viele ticks bis zur Explosion uebrig sind
	int isActive;		// ob die Bombe existiert
}

// sollte im Menue abgefragt werden
const int playerCount;

// Anzahl an Bomben pro Spieler
const int bombsPerPlayer;

// maximale Anzahl von Bomben im Spiel
// bzw. (Bomben pro Spieler) * Spieleranzahl
const int maxBombCount = bombsPerPlayer * playerCount;

// Liste von Spielerstructs
struct player players[playerCount];

// Liste von Bombenstructs
struct bomb bombs[maxBombCount*playerCount];

// Spieler an Spawnpunkten initialisieren
void initPlayers(int playerCount, /*FIXME*/ SPAWNPOINTS) {
	for (int i = 0; i < playerCount; i++) {
		players[i].x = SPAWNPOINT_X;
		players[i].y = SPAWNPOINT_Y;
		players[i].ch = '@';
		players[i].Bombs = bombsPerPlayer;
		players[i].isDead = 0;
		players[i].isActive = 0;
	}
}

void initBombs(int maxBombCount) {
	for (int i = 0; i < maxBombCount; i++) {
		bombs[i].x = 0;
		bombs[i].y = 0;
		bombs[i].radius = 0;
		bombs[i].timer = 0;
		bombs[i].isActive = 0;
	}
}

// prueft ob der Spieler x noch Bomben zum setzen hat
int hasBomb(int playerIndex) {
	return (players[playerIndex].bombs);
}

// das Bomben-array wird so aufgeteilt, dass der erste Spieler die ersten x
// Bombenslots zugewiesen werden, und auf die einzelnen ueber die bombsPlaced
// Variable zugegriffen wird
int plantBomb(int playerIndex) {
	if (hasBomb(playerIndex)) {
		// belege ihn, wenn es einen freien Bombenslot gibt
		if ((int slot = findFreeBombSlot()) != -1) {
			bombs[slot].x = players[playerIndex].;
			bombs[slot].y = players[playerIndex].;
			bombs[slot].radius = RADIUS; //FIXME
			bombs[slot].timer = EXPLODETIME;//FIXME
			bombs[slot].isActive = 1;
		}
	}
	
}

// findet einen freien Bombenslot (im bombs-array) und gibt ihn aus
int findFreeBombSlot(void) {
	for (int i = 0; i < maxBombCount; i++) {
		if (bombs[i].isActive) {
			return (i);
		}
	}
	return (-1); // falls kein Slot frei ist wird -1 zurueckgegeben
}

// Bombentimer dekrementieren und Bomben explodieren lassen
void tickBombs() {
	for (int i = 0; i < maxBombCount; i++) {
		// wenn der Bombenslot aktiv ist
		if (bombs[i].isActive) {
			if (bombs[i].timer < 1) {
				explodeBomb(i);
			} else {
				bombs[i].timer--;
			}
			
		}
	}
}

// Spieler Bomben geben, falls die maximale Bombenanzahl nicht erreicht ist
// alle paar Sekunden aufrufen
int giveBomb(int playerIndex) {
	if (players[playerIndex].bombs < bombsPerPlayer) {
		players[playerIndex].bombs++;
	}
}

void explodeBomb(bombIndex) {
	explosion(bomb[bombIndex].x, bomb[bombIndex].y, EXPLTIME, RADIUS); //FIXME
}

// Schadensarray mit Nullen initialisieren
int DAMAGE_ARRAY[width*height] = {0};

// arbeitet auf dem Damagearray
// 'time' ist die Zeit die die Explosion auf der map bleiben soll
// (und Schaden austeilen)
// 'radius' beschreibt den Explosionsradius 
void explosion(int x, int y, int time, int radius){
	DAMAGE_ARRAY[x+(y*width)] = time;
	int UP = 0;
	int DOWN = 0;
	int LEFT = 0;
	int RIGHT = 0;
	// expandiere Explosion solange der naechste Schritt kein solid ist
	// (bis radius erreich ist)
	while (!directionNonSolid(DAMAGE_ARRAY, x, y, 'u') && UP < radius) {
		UP++;
		DAMAGE_ARRAY[x+((y-UP)*width)] = time;
	}
	while (!directionNonSolid(DAMAGE_ARRAY, x, y, 'd') && DOWN < radius) {
		DOWN++;
		DAMAGE_ARRAY[x+((y+DOWN)*width)] = time;
	}
	while (!directionNonSolid(DAMAGE_ARRAY, x, y, 'l') && LEFT < radius) {
		LEFT++;
		DAMAGE_ARRAY[x-LEFT+(y*width)] = time;
	}
	while (!directionNonSolid(DAMAGE_ARRAY, x, y, 'r') && RIGHT < radius) {
		RIGHT++;
		DAMAGE_ARRAY[x+RIGHT+(y*width)] = time;
	}
}

// pruefe und toete Spieler
// gibt Anzahl lebendiger Spieler zurueck
int checkPlayerKill(void) {
	int alivePlayerCount = 0;
	for (int i = 0; i < playerCount; i++) {
		if ((!players[i].isDead || players[i].isActive) {
			if (DAMAGE_ARRAY[players[i].x + (players[i].y * WIDTH)]) {
				players[i].isDead = 1;
			}
		alivePlayerCount++:
		}
	}
	return (alivePlayerCount);
}

// 
int checkPlayerWin(void) {
	
}
