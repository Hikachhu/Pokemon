#include "All_Include.h"

void Deplacement(int ch,int *posY,int *posX){
	mvprintw((*posY), (*posX)," ");
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
	mvprintw((*posY), (*posX), "#");
	refresh();
}

void AffichageLigne(int longeur,int y,int x){
//	FILE *fichier=fopen("PositionImpossible.txt","a");
	for (int i = 0; i < longeur; i++) {
		mvprintw(y,x+1+i,"_");
//		fprintf(fichier, "%d %d ",y,x+1+i );
		refresh();
	}
//	fprintf(fichier,"\n");
//	fclose(fichier);
}

void AffichageColonne(int longeur,int y,int x){
//	FILE *fichier=fopen("PositionImpossible.txt","a");
	for (int i = 0; i < longeur; i++) {
		mvprintw(y+1+i,x,"|");
//		fprintf(fichier, "%d %d ",y+1+i,x );
		refresh();
	}
//	fprintf(fichier,"\n");
//	fclose(fichier);
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

	mvprintw(5,35,"m");

	refresh();
}
