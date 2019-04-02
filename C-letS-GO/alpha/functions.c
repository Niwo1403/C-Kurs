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
			//FIXME ARRAY_XMAXdurch Array-Breite ersetzen
			if (x == ARRAY_XMAX) {
				return (1)
			} else {
				return(array[x+1+(y*width)]);
			}
}

// arbeitet auf dem Damagearray
// 'time' ist die Zeit die die Explosion auf der map bleiben soll
// (und Schaden austeilen)
// 'radius' beschreibt den Explosionsradius 
void explodeBomb(int x, int y, int time, int radius){
	DAMAGE_ARRAY[x+(y*width)] = time;
	int UP = 0;
	int DOWN = 0;
	int LEFT = 0;
	int RIGHT = 0;
	// solange der naechste kein solid ist: expandiere Explosion
	// bis radius erreich ist
	while (!directionNonSolid(DAMAGE_ARRAY, x, y, 'u') && UP < radius) {
		UP++;
		DAMAGE_ARRAY[x+((y-UP)*width)] = time;
	}
	while (!directionNonSolid(DAMAGE_ARRAY, x, y, 'd') && DOWN < radius) {
		DOWN++;
		DAMAGE_ARRAY[x+((y-UP)*width)] = time;
	}
	while (!directionNonSolid(DAMAGE_ARRAY, x, y, 'l') && LEFT < radius) {
		LEFT++;
		DAMAGE_ARRAY[x+((y-UP)*width)] = time;
	}
	while (!directionNonSolid(DAMAGE_ARRAY, x, y, 'r') && RIGHT < radius) {
		RIGHT++;
		DAMAGE_ARRAY[x+((y-UP)*width)] = time;
	}
}

void decrementMap() {
	
}

struct Player {
	int x;		// Position auf der map
	int y;
	int Bombs;	// Anzahl der Bomben im Inventar
	int isDead;
}


