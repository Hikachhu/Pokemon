#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct Node Node;
typedef struct Pokemon Pokemon;
typedef struct Joueur Joueur;
typedef struct att att;

struct Node{
	Pokemon *Actuel;
	Node *LeftSon;
	Node *RightSon;
};

struct Joueur{
	int PositionX;
	int PositionY;
	Pokemon *pokemon1;
	Pokemon *pokemon2;
	Pokemon *pokemon3;
	int Argent;
};

struct att{
	int Dommage;
	char Nom[10];
};

struct Pokemon{
	char Name[14];
  size_t Number;
  size_t Level;
  size_t att;
  size_t def;
  size_t hp;
  size_t speed;
  size_t ActualHp;
  size_t ActualXp;
	att Attaques[4];
};

void ncurses_initialiser() {
  initscr();	        /* Demarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Desactive l'affichage des caracteres saisis */
  keypad(stdscr, TRUE);	/* Active les touches specifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}

void Ordre(Node *noeud){
  if (noeud!=NULL){
			Ordre((*noeud).LeftSon);
			printf("%ld\t",noeud->Actuel->Number);
			printf("%ld\t",noeud->Actuel->Level);
			printf("%ld\t",noeud->Actuel->hp);
			printf("%ld\t",noeud->Actuel->att);
			printf("%ld\t",noeud->Actuel->def);
			printf("%ld\t",noeud->Actuel->speed);
			printf("%s\t",noeud->Actuel->Name);
      printf("\n");
			Ordre((*noeud).RightSon);
  }
}

void DestructionTotal(Node *Actuel){
	if(Actuel!=NULL){
		DestructionTotal((*Actuel).LeftSon);
		DestructionTotal((*Actuel).RightSon);
		(*Actuel).RightSon=NULL;
		(*Actuel).LeftSon=NULL;
		Actuel=NULL;
		free(Actuel);
	}
}

Node *Ajout(Node *Noeud,Pokemon *pokemon) {
  if (Noeud==NULL){
		Node *Nouveau=NULL;
    Nouveau=(Node*)malloc(sizeof(Nouveau));
    (Nouveau->Actuel)=(pokemon);
    (*Nouveau).RightSon=NULL;
    (*Nouveau).LeftSon=NULL;
    return Nouveau;
  }
  else{
    if (Noeud->Actuel->Number<pokemon->Number){
      (*Noeud).RightSon=Ajout((*Noeud).RightSon,pokemon);
    }
    else{
      (*Noeud).LeftSon=Ajout((*Noeud).LeftSon,pokemon);
    }
  }
}

Pokemon *LectureListePokemon(FILE *fichier){
  Pokemon *Nouveau;
  Nouveau=(Pokemon*)malloc(sizeof(Pokemon));
	Nouveau->Level=1;
  fscanf(fichier,"%ld %ld %ld %ld %ld",&(Nouveau->Number),&(Nouveau->hp),&(Nouveau->att),&(Nouveau->def),&(Nouveau->speed));
	fgets(Nouveau->Name,14,fichier);
//	printf("%ld %ld %ld %ld %ld %s\n",(Nouveau->Number),(Nouveau->hp),(Nouveau->att),(Nouveau->def),(Nouveau->speed),Nouveau->Name);
  return Nouveau;
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

	refresh();
}

void CombatNature(Joueur *Player,Pokemon *PokemonAleatoire){
	mvprintw(20,73,"Pokemon:%s",Player->pokemon1->Name);
	mvprintw(21,73,"Contre:%s",PokemonAleatoire->Name);
	refresh();
}

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

Pokemon *RecherchePokemonStat(Node *PokemonActuel,int numero){
	if (PokemonActuel==NULL){
		return 0;
	}
	else if((PokemonActuel->Actuel->Number)==numero){
		return (PokemonActuel->Actuel);
	}
	else
	{
		if((PokemonActuel->Actuel->Number)>numero){
			return RecherchePokemonStat((*PokemonActuel).LeftSon,numero);
		}
		if((PokemonActuel->Actuel->Number)<numero){
			return RecherchePokemonStat((*PokemonActuel).RightSon,numero);
		}
	}
}

void RencontreAleatoire(Joueur *Player,Node *ListePokemon){
	int Rencontre,PokemonAleatoire;
	Pokemon *PokemonRencontre;
	Rencontre=rand()%20;
	if((Rencontre)==0){
		switch (rand()%500){
			case 0 ... 24://1 ->5%
				PokemonAleatoire=1;
				break;
			case 25 ... 49://2 ->5%
				PokemonAleatoire=3;
				break;
			case 50 ... 74://3 ->5%
				PokemonAleatoire=5;
				break;
			case 75 ... 99://4 ->5%
				PokemonAleatoire=11;
				break;
			case 100 ... 124://5 ->5%
				PokemonAleatoire=12;
				break;
			case 125 ... 149://6 ->5%
				PokemonAleatoire=14;
				break;
			case 150 ... 174://7 ->5%
				PokemonAleatoire=16;
				break;
			case 175 ... 199://8 ->5%
				PokemonAleatoire=18;
				break;
			case 200 ... 224://9 ->5%
				PokemonAleatoire=20;
				break;
			case 225 ... 249://10 ->5%
				PokemonAleatoire=22;
				break;
			case 250 ... 274://11 ->5%
				PokemonAleatoire=24;
				break;
			case 275 ... 324://12 ->10%
				PokemonAleatoire=7;
				break;
			case 325 ... 374://13 ->10%
				PokemonAleatoire=9;
				break;
			case 375 ... 424://14 ->10%
				PokemonAleatoire=26;
				break;
			case 425 ... 444://15 ->4%
				PokemonAleatoire=28;
				break;
			case 445 ... 464://16 ->4%
				PokemonAleatoire=29;
				break;
			case 465 ... 484://17 ->4%
				PokemonAleatoire=30;
				break;
			case 485 ... 499://18 ->3%
				PokemonAleatoire=31;
				break;
		}
		CombatNature(Player,RecherchePokemonStat(ListePokemon,PokemonAleatoire));

		}
}

Joueur *ChoixStarter(Node*ListePokemon){
	int Touche;
	Joueur *Player=(Joueur*)malloc(sizeof(Player));
	mvprintw(LINES/2-1,COLS/2,"Entrez le numero du pokemon voulu pour commencer");
	mvprintw(LINES/2,COLS/2,"Bulbizarre Salameche Carapuce");
	mvprintw(LINES/2 +1,COLS/2,"1             2         3");
	refresh();
	do{
		Touche=getch();
		mvprintw(LINES/2 +2,COLS/2,"%d",Touche);
		switch (Touche){
			case 49:
				Player->pokemon1=RecherchePokemonStat(ListePokemon,1);
				break;
			case 50:
				Player->pokemon1=RecherchePokemonStat(ListePokemon,2);
				break;
			case 51:
				Player->pokemon1=RecherchePokemonStat(ListePokemon,3);
				break;
		}
	}while((Touche!=49)&&(Touche!=50)&&(Touche!=51));
}

int main(){
	srand(time(NULL));
	int ChoixPartie,ch,posX,posY,PokemonAleatoire=0,Rencontre=0;
	Node *ListePokemon=NULL;
	FILE *fichier=NULL;
	Pokemon *test=NULL,*PokemonRencontre=NULL;
	Joueur *Player=NULL;
	system("clear");
	printf("Voulez-vous démarrer une nouvelle partie ?(1=Nouvelle partie/2=Ancienne partie)");
	scanf("%d",&ChoixPartie);
	printf("Choix=%d\n",ChoixPartie);
	fichier=fopen("ListePokemon.txt","r");
	if(fichier==NULL) printf("Erreur ouverture fichier");
	for (size_t i = 1; i <= 31; i++) {
		test=LectureListePokemon(fichier);
		ListePokemon=Ajout(ListePokemon,test);
	}
	//Ordre(ListePokemon);
	ncurses_initialiser();
	if(ChoixPartie==1){
		Player=ChoixStarter(ListePokemon);
	}
	sleep(1);
	erase();
	AffichageCarte();
	AffichageColonne(45,0,70);
	mvprintw(38,48,"#");
	refresh();
	posX=48;posY=38;
//#########################Boucle principale de jeu#########################################
	do {
	    /* On efface le curseur */
	    if( (ch ==KEY_LEFT)||(ch ==KEY_RIGHT)||(ch ==KEY_UP)||(ch ==KEY_DOWN)){
				Deplacement(ch,&posY,&posX);
	    }
			refresh();
			if ((posX<=49)&&(posX>=30)&&(posY<=20)&&(posY>=16)||((posX<=49)&&(posX>=41)&&(posY<=29)&&(posY>=20))){
				RencontreAleatoire(Player,ListePokemon);
			}
			mvprintw(29,75,"Utilisez les touches directionnels pour vous deplacez");
			mvprintw(30,75,"Press f3 pour sortir");
			refresh();
	} while((ch = getch()) != KEY_F(3));
//##########################################################################################
  DestructionTotal(ListePokemon);
	free(ListePokemon);
	free(test);
  fclose(fichier);
	endwin();
  return 0;
}
