void AffichageCarte();
void AffichageLigne(int longeur,int y,int x);
void AffichageColonne(int longeur,int y,int x);
void Deplacement(int ch,int *posY,int *posX);

void Deplacement(int ch,int *posY,int *posX){
	mvprintw((*posY), (*posX)," ");
	/* On calcule la nouvelle position */
	switch(ch) {
		case KEY_LEFT:
			if((*posX) > 0) (*posX)--;
				break;
		case KEY_RIGHT:
			if((*posX) < COLS - 1) (*posX)++;
				break;
		case KEY_UP:
			if((*posY) > 0) (*posY)--;
				break;
		case KEY_DOWN:
			if((*posY) < LINES - 1) (*posY)++;
				break;
	}
	/* On affiche le curseur */
	mvprintw((*posY), (*posX), "#");
	refresh();
}

void AffichageLigne(int longeur,int y,int x){
	for (size_t i = 0; i < longeur; i++) {
		mvprintw(y,x+1+i,"_");
		refresh();
	}
}

void AffichageColonne(int longeur,int y,int x){
	for (size_t i = 0; i < longeur; i++) {
		mvprintw(y+1+i,x,"|");
		refresh();
	}
}

void AffichageCarte() {
	AffichageColonne(10,1,1);
	AffichageLigne(40,1,1);
	AffichageColonne(10,1,42);
	AffichageLigne(20,11,1);
	AffichageLigne(14,11,27);
	AffichageColonne(10,11,22);
	AffichageColonne(4,11,27);
	AffichageLigne(24,15,27);
	AffichageLigne(16,21,22);
	AffichageColonne(25,15,52);
	AffichageColonne(10,21,39);
	AffichageLigne(20,31,18);
	AffichageColonne(9,31,18);
	AffichageLigne(33,40,18);

	AffichageColonne(4,16,30);
	AffichageColonne(4,16,49);
	AffichageLigne(18,16,30);
	AffichageLigne(10,20,30);

	AffichageColonne(9,20,41);
	AffichageColonne(9,20,49);
	AffichageLigne(7,29,41);

	AffichageColonne(45,0,70);

	refresh();
}
