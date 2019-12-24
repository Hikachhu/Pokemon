#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <color.h>

typedef struct NodePokemon NodePokemon;
typedef struct NodeAtt NodeAtt;
typedef struct Pokemon Pokemon;
typedef struct Joueur Joueur;
typedef struct att att;

struct NodePokemon{
	Pokemon *Actuel;
	NodePokemon *LeftSon;
	NodePokemon *RightSon;
};

struct NodeAtt{
	att *Actuel;
	NodeAtt *LeftSon;
	NodeAtt *RightSon;
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
	int Number;
	int Dommage;
	char Name[13];
};

struct Pokemon{
	char Name[14];
  size_t Number;
  size_t Level;
  size_t att;
  size_t def;
  size_t hp;
  size_t speed;
  int ActualHp;
  size_t ActualXp;
	att *Attaques[4];
};

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void AffichageName(char Name[14]){
	for (size_t i = 0; i < 14; i++) {
		mvprintw(i,140,"%c",Name[i]);
	}
}

void EgaliteEntreTableau(char Destination[14],char Origine[14]){
	for (size_t i = 0; i < 14; i++) {
		Destination[i]=Origine[i];
	}
}

void ModificationName(char Name[14]){
	for (size_t i = 0; i < 14; i++) {
		if(Name[i]==10) Name[i]='\0';
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

/*
void Ordre(NodePokemon *noeud){
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
}*/

void Ordre(NodeAtt *noeud){
  if (noeud!=NULL){
			Ordre((*noeud).LeftSon);
			printf("%d\t",noeud->Actuel->Number);
			printf("%d\t",noeud->Actuel->Dommage);
			printf("%s\t",noeud->Actuel->Name );
      printf("\n");
			Ordre((*noeud).RightSon);
  }
}

void DestructionTotal(NodePokemon *Actuel){
	if(Actuel!=NULL){
		DestructionTotal((*Actuel).LeftSon);
		DestructionTotal((*Actuel).RightSon);
		free(Actuel->RightSon->Actuel->Attaques[0]);
		free(Actuel->RightSon->Actuel->Attaques[1]);
		free(Actuel->LeftSon->Actuel->Attaques[0]);
		free(Actuel->LeftSon->Actuel->Attaques[1]);
		(*Actuel).RightSon=NULL;
		(*Actuel).LeftSon=NULL;
		free(Actuel);
		Actuel=NULL;
	}
}

NodeAtt *AjoutAttaque(NodeAtt *Noeud,att *attaques) {
  if (Noeud==NULL){
		NodeAtt *Nouveau=NULL;
    Nouveau=(NodeAtt*)malloc(sizeof(Nouveau));
    (Nouveau->Actuel)=(attaques);
    (*Nouveau).RightSon=NULL;
    (*Nouveau).LeftSon=NULL;
    return Nouveau;
  }
  else{
    if (Noeud->Actuel->Number<attaques->Number){
      (*Noeud).RightSon=AjoutAttaque((*Noeud).RightSon,attaques);
    }
    else{
      (*Noeud).LeftSon=AjoutAttaque((*Noeud).LeftSon,attaques);
    }
  }
}

NodePokemon *AjoutPokemon(NodePokemon *Noeud,Pokemon *pokemon) {
  if (Noeud==NULL){
		NodePokemon *Nouveau=NULL;
    Nouveau=(NodePokemon*)malloc(sizeof(Nouveau));
    (Nouveau->Actuel)=(pokemon);
    (*Nouveau).RightSon=NULL;
    (*Nouveau).LeftSon=NULL;
    return Nouveau;
  }
  else{
    if (Noeud->Actuel->Number<pokemon->Number){
      (*Noeud).RightSon=AjoutPokemon((*Noeud).RightSon,pokemon);
    }
    else{
      (*Noeud).LeftSon=AjoutPokemon((*Noeud).LeftSon,pokemon);
    }
  }
}

Pokemon *LectureListePokemon(FILE *fichier){
  Pokemon *Nouveau;
	char Nom[13];
  Nouveau=(Pokemon*)malloc(sizeof(Pokemon));
	Nouveau->Attaques[0]=(att*)malloc(sizeof(att));
	Nouveau->Attaques[1]=(att*)malloc(sizeof(att));
	Nouveau->Level=1;
  fscanf(fichier,"%ld",&(Nouveau->Number));
	fscanf(fichier,"%ld",&(Nouveau->hp));
	fscanf(fichier,"%ld",&(Nouveau->att));
	fscanf(fichier,"%ld",&(Nouveau->def));
	fscanf(fichier,"%ld",&(Nouveau->speed));
	Nouveau->ActualHp=(int)(Nouveau->hp);
	Nouveau->ActualXp=0;
	fscanf(fichier,"%d",&(Nouveau->Attaques[0]->Number));
	fscanf(fichier,"%d",&(Nouveau->Attaques[1]->Number));

	fgets(Nom,13,fichier);
	ModificationName(Nom);
	EgaliteEntreTableau(Nouveau->Name,Nom);
//	printf("%ld %ld %ld %ld %ld %s\n",(Nouveau->Number),(Nouveau->hp),(Nouveau->att),(Nouveau->def),(Nouveau->speed),Nouveau->Name);
  return Nouveau;
}

att *LectureListeAtt(FILE *fichier){
  att *Nouveau;
	char Nom[14];
  Nouveau=(att*)malloc(sizeof(att));
  fscanf(fichier,"%d %d",&(Nouveau->Number),&(Nouveau->Dommage));
	fgets(Nom,14,fichier);
	ModificationName(Nom);
	EgaliteEntreTableau(Nouveau->Name,Nom);
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

	AffichageColonne(45,0,70);

	refresh();
}

void CombatNature(Joueur *Player,Pokemon *PokemonAleatoire){
	int AttaqueChoisi=0,DegatPlayer=0,DegatAdversaire=0,AttaqueAleatoire=0,c;
	AffichageName(Player->pokemon1->Name);
	mvprintw(11,73,"Pokemon:%s",Player->pokemon1->Name);
	mvprintw(11,95,"Attaque 1:%s",Player->pokemon1->Attaques[0]->Name);
	mvprintw(12,95,"Attaque 2:%s",Player->pokemon1->Attaques[1]->Name);

	mvprintw(14,73,"Contre:%s",PokemonAleatoire->Name);
	mvprintw(14,95,"Attaque 1:%s",PokemonAleatoire->Attaques[0]->Name);
	mvprintw(15,95,"Attaque 2:%s",PokemonAleatoire->Attaques[1]->Name);
	refresh();
	do{
		mvprintw(17,73,"Attaque 1 ou Attaque 2");
		mvprintw(12,73,"Vie Actuel:   ",Player->pokemon1->ActualHp);
		mvprintw(12,73,"Vie Actuel:%d",Player->pokemon1->ActualHp);
		mvprintw(15,73,"Vie Actuel:   ",PokemonAleatoire->ActualHp);
		mvprintw(15,73,"Vie Actuel:%d",PokemonAleatoire->ActualHp);
		refresh();
		do {
			AttaqueChoisi=getch();
			mvprintw(18,73,"   ");
			mvprintw(18,73,"%d",AttaqueChoisi);
			refresh();
		} while(AttaqueChoisi!=49&&AttaqueChoisi!=50);
		mvprintw(19,73,"Vous avez choisi %s           ",Player->pokemon1->Attaques[AttaqueChoisi-49]->Name);
		refresh();
		AttaqueAleatoire=rand()%2;
		DegatPlayer=( (((Player->pokemon1->Level)*(4)+2)*(Player->pokemon1->Attaques[AttaqueChoisi-49]->Dommage)*(Player->pokemon1->att)+2)/((PokemonAleatoire->def)*50) );
		DegatAdversaire=((((PokemonAleatoire->Level)*(4)+2)*(PokemonAleatoire->Attaques[AttaqueAleatoire]->Dommage)*(PokemonAleatoire->att)+2)/((Player->pokemon1->def)*50));
		mvprintw(20,73,"Degat au pokemon adversaire:   ",DegatPlayer);
		mvprintw(20,73,"Degat au pokemon adversaire:%d",DegatPlayer);
		mvprintw(21,73,"Degat au pokemon allie:    ",DegatAdversaire);
		mvprintw(21,73,"Degat au pokemon allie:%d",DegatAdversaire);
		refresh();
		Player->pokemon1->ActualHp =(Player->pokemon1->ActualHp-DegatAdversaire);
		PokemonAleatoire->ActualHp =(PokemonAleatoire->ActualHp-DegatPlayer);

	}while(((Player->pokemon1->ActualHp)>0)&&((PokemonAleatoire->ActualHp)>0));
	if (PokemonAleatoire->ActualHp>0)
		mvprintw(22,73,"Vous avez perdu le combat");
	else
		mvprintw(22,73,"Vous avez gagne");
	mvprintw(23,73,"Pressez 'a' pour continuez");
	refresh();
	do {
		c=getchar();
	} while(c!=97);
	erase();
	AffichageCarte();
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

att *RechercheAttaquesStat(NodeAtt *AttaqueActuel,int numero){
	if (AttaqueActuel==NULL){
		return 0;
	}
	else if((AttaqueActuel->Actuel->Number)==numero){
		return (AttaqueActuel->Actuel);
	}
	else
	{
		if((AttaqueActuel->Actuel->Number)>numero){
			return RechercheAttaquesStat((*AttaqueActuel).LeftSon,numero);
		}
		if((AttaqueActuel->Actuel->Number)<numero){
			return RechercheAttaquesStat((*AttaqueActuel).RightSon,numero);
		}
	}
}

Pokemon *RecherchePokemonStat(NodePokemon *PokemonActuel,int numero){
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

void AssociationAttaqueAPokemon(NodeAtt *ArbreAtt,Pokemon *pokemon){
	pokemon->Attaques[0]=RechercheAttaquesStat(ArbreAtt,pokemon->Attaques[0]->Number);
	pokemon->Attaques[1]=RechercheAttaquesStat(ArbreAtt,pokemon->Attaques[1]->Number);
}

Joueur *ChoixStarter(NodeAtt *ArbreAtt,NodePokemon*ListePokemon){
	int Touche;
	Joueur *Player=(Joueur*)malloc(sizeof(Player));
	mvprintw(LINES/2-1,COLS/2,"Entrez le numero du pokemon voulu pour commencer");
	mvprintw(LINES/2,COLS/2,"Bulbizarre Salameche Carapuce");
	mvprintw(LINES/2 +1,COLS/2,"1             2         3");
	refresh();
	do{
		Touche=getch();
		switch (Touche){
			case 49:
			Player->pokemon1=RecherchePokemonStat(ListePokemon,1);
			break;
			case 50:
			Player->pokemon1=RecherchePokemonStat(ListePokemon,3);
			break;
			case 51:
			Player->pokemon1=RecherchePokemonStat(ListePokemon,5);
			break;
		}
	}while((Touche!=49)&&(Touche!=50)&&(Touche!=51));
	AssociationAttaqueAPokemon(ArbreAtt,Player->pokemon1);
	return Player;
}

void RencontreAleatoire(Joueur *Player,NodePokemon *ListePokemon,NodeAtt *ArbreAtt){
	int Rencontre,PokemonAleatoire;
	Pokemon *PokemonRencontre;
	Rencontre=rand()%5;
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
			Pokemon *PokemonRandom=RecherchePokemonStat(ListePokemon,PokemonAleatoire);
			AssociationAttaqueAPokemon(ArbreAtt,PokemonRandom);
			CombatNature(Player,PokemonRandom);
		}
}

int main(){
	srand(time(NULL));
	int ChoixPartie,ch,posX,posY,PokemonAleatoire=0,Rencontre=0;
	NodePokemon *ListePokemon=NULL;
	NodeAtt *ListeAttaques=NULL;
	FILE *fichier=NULL;
	Pokemon *test=NULL,*PokemonRencontre=NULL;
	att *attaques=NULL;
	Joueur *Player=NULL;
	system("clear");
	printf("Voulez-vous démarrer une nouvelle partie ?(1=Nouvelle partie/2=Ancienne partie)");
	scanf("%d",&ChoixPartie);
	printf("Choix=%d\n",ChoixPartie);
	fichier=fopen("ListePokemon.txt","r");
	if(fichier==NULL) printf("Erreur ouverture fichier");
	for (size_t i = 1; i <= 31; i++) {
		test=LectureListePokemon(fichier);
		ListePokemon=AjoutPokemon(ListePokemon,test);
	}
	fclose(fichier);
	fichier=fopen("ListeAttaques.txt","r");
	for (size_t i = 0; i < 3; i++) {
		attaques=LectureListeAtt(fichier);
		ListeAttaques=AjoutAttaque(ListeAttaques,attaques);
	}

//	Ordre(ListeAttaques);
	ncurses_initialiser();
	if(ChoixPartie==1){
		Player=ChoixStarter(ListeAttaques,ListePokemon);
		refresh();
	}
	erase();
	AffichageCarte();
	mvprintw(38,48,"#");
	refresh();
	posX=48;posY=38;
//#########################Boucle principale de jeu#########################################
	do {
	    /* On efface le curseur */
	    if( (ch ==KEY_LEFT)||(ch ==KEY_RIGHT)||(ch ==KEY_UP)||(ch ==KEY_DOWN)){
				Deplacement(ch,&posY,&posX);
				Player->PositionX=posX;
				Player->PositionY=posY;
	    }
			refresh();
			if ((posX<=49)&&(posX>=30)&&(posY<=20)&&(posY>=16)||((posX<=49)&&(posX>=41)&&(posY<=29)&&(posY>=20))){
				RencontreAleatoire(Player,ListePokemon,ListeAttaques);
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
