#include <curses.h>
#include "All_Include.h"

int VerificationMur(ControleFile *TeteDeFile,int ch,int posX,int posY){
	ElementFile *ElementActuel= TeteDeFile->PremierElement;
	int PosYAVerifier=posY,PosXAVerifier=posX;
	switch(ch) {
		case KEY_LEFT:
				PosXAVerifier--;
				break;
		case KEY_RIGHT:
				PosXAVerifier++;
				break;
		case KEY_UP:
				PosYAVerifier--;
				break;
		case KEY_DOWN:
				PosYAVerifier++;
				break;
	}
	mvprintw(40,73,"Futur position A verifier x:%d y:%d",PosXAVerifier,PosYAVerifier);
	while (ElementActuel != NULL){
		if(PosYAVerifier==ElementActuel->PosY && PosXAVerifier==ElementActuel->PosX)
			return 0;
		ElementActuel = ElementActuel->ElementSuivant;
	}
	mvprintw(40,73,"                                       ");
	return 1;
}

void StatPlayer(Joueur *Player){
  printw("%d ",Player->pokemon[0]->Number);
  printw("Nom du pokemon:%s ",Player->pokemon[0]->Name);
  printw("Level:%d ",Player->pokemon[0]->Level);
  printw("Xp Actuel:%d ",Player->pokemon[0]->ActualXp);
  printw("%d ",Player->PositionX);
  printw("%d",Player->PositionY);
  refresh();
}

void ModificationName(char Name[14]){
	for (size_t i = 0; i < 14; i++) {
		if(Name[i]==10) Name[i]='\0';
	}
}

void EgaliteEntreTableau(char Destination[14],char Origine[14]){
	for (size_t i = 0; i < 14; i++) {
		Destination[i]=Origine[i];
	}
}

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

void ncurses_initialiser() {
  initscr();	        /* Demarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Desactive l'affichage des caracteres saisis */
  keypad(stdscr, TRUE);	/* Active les touches specifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}
