#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Suppression.h"
#include "Outils.h"
#include "AffichageNcurses.h"

Pokemon *CopiePokemon(Pokemon *PokemonOrigine){
	Pokemon *PokemonCible=(Pokemon*)malloc(sizeof(Pokemon));
	PokemonCible->Attaques[0]=(att*)malloc(sizeof(att));
	PokemonCible->Attaques[1]=(att*)malloc(sizeof(att));

	PokemonCible->Number=PokemonOrigine->Number;
	EgaliteEntreTableau(PokemonCible->Name,PokemonOrigine->Name);
	PokemonCible->Level=PokemonOrigine->Level;
	PokemonCible->att=PokemonOrigine->att;
	PokemonCible->def=PokemonOrigine->hp;
	PokemonCible->speed=PokemonOrigine->speed;
	PokemonCible->xpNextLevel=PokemonOrigine->xpNextLevel;
	PokemonCible->ActualXp=PokemonOrigine->ActualXp;
	PokemonCible->ActualHp=PokemonOrigine->ActualHp;
	PokemonCible->Attaques[0]=PokemonOrigine->Attaques[0];
	PokemonCible->Attaques[1]=PokemonOrigine->Attaques[1];
	return PokemonCible;
}

void AffichageName(char Name[14]){
	for (size_t i = 0; i < 14; i++) {
		mvprintw(i,140,"%c",Name[i]);
	}
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
	fscanf(fichier,"%d",&(Nouveau->xpNextLevel));
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

void CombatNature(Joueur *Player,Pokemon *PokemonAleatoire){
	mvprintw(5,73,"Debug:%d",Player->pokemon1->xpNextLevel);
	int AttaqueChoisi=0,DegatPlayer=0,DegatAdversaire=0,AttaqueAleatoire=0,c,VieAvantCombatAllie=Player->pokemon1->ActualHp,VieAvantCombatEnnemi=PokemonAleatoire->ActualHp;
	mvprintw(9,73,"Pokemon:%s",Player->pokemon1->Name);
	mvprintw(9,95,"Attaque 1:%s",Player->pokemon1->Attaques[0]->Name);
	mvprintw(10,95,"Attaque 2:%s",Player->pokemon1->Attaques[1]->Name);
	mvprintw(11,73,"Experience Actuel:%d/%d",Player->pokemon1->ActualXp,(Player->pokemon1->xpNextLevel+15*Player->pokemon1->Level));

	mvprintw(13,73,"Contre:%s",PokemonAleatoire->Name);
	mvprintw(13,95,"Attaque 1:%s",PokemonAleatoire->Attaques[0]->Name);
	mvprintw(14,95,"Attaque 2:%s",PokemonAleatoire->Attaques[1]->Name);
	refresh();
	do{
		mvprintw(17,73,"Attaque 1 ou Attaque 2");
		mvprintw(10,73,"Vie Actuel:   ",Player->pokemon1->ActualHp);
		mvprintw(10,73,"Vie Actuel:%d",Player->pokemon1->ActualHp);
		mvprintw(14,73,"Vie Actuel:   ",PokemonAleatoire->ActualHp);
		mvprintw(14,73,"Vie Actuel:%d",PokemonAleatoire->ActualHp);
		refresh();
		do {
			AttaqueChoisi=getch();
			refresh();
		} while(AttaqueChoisi!=49&&AttaqueChoisi!=50);
		mvprintw(19,73,"Vous avez choisi %s           ",Player->pokemon1->Attaques[AttaqueChoisi-49]->Name);
		refresh();
		AttaqueAleatoire=rand()%2;
		DegatPlayer=( (((Player->pokemon1->Level)*(4)+2)*(Player->pokemon1->Attaques[AttaqueChoisi-49]->Dommage)*((Player->pokemon1->att)+Player->pokemon1->att)+2)/((PokemonAleatoire->def+PokemonAleatoire->Level)*50) );
		DegatAdversaire=((((PokemonAleatoire->Level)*(4)+2)*(PokemonAleatoire->Attaques[AttaqueAleatoire]->Dommage)*(PokemonAleatoire->att+PokemonAleatoire->Level)+2)/((Player->pokemon1->def+Player->pokemon1->Level)*50));
		mvprintw(20,73,"Degat au pokemon adversaire:   ",DegatPlayer);
		mvprintw(20,73,"Degat au pokemon adversaire:%d",DegatPlayer);
		mvprintw(21,73,"Degat au pokemon allie:    ",DegatAdversaire);
		mvprintw(21,73,"Degat au pokemon allie:%d",DegatAdversaire);
		refresh();
		Player->pokemon1->ActualHp =(Player->pokemon1->ActualHp-DegatAdversaire);
		PokemonAleatoire->ActualHp =(PokemonAleatoire->ActualHp-DegatPlayer);

	}while(((Player->pokemon1->ActualHp)>0)&&((PokemonAleatoire->ActualHp)>0));
	if (PokemonAleatoire->ActualHp>0){
		mvprintw(22,73,"Vous avez perdu le combat");
	}
	else{
		Player->pokemon1->ActualXp+=((Player->pokemon1->Level+2)*(PokemonAleatoire->Level+2)+3);
		mvprintw(22,73,"Vous avez gagne");
		if ((Player->pokemon1->ActualXp)>=(Player->pokemon1->xpNextLevel+(Player->pokemon1->Level)*15)){
			Player->pokemon1->ActualXp=(Player->pokemon1->ActualXp-(Player->pokemon1->xpNextLevel+(Player->pokemon1->Level)*15));
			(Player->pokemon1->Level)++;
		}
	}
	mvprintw(23,73,"Pressez 'a' pour continuez");
	refresh();
	do {
		c=getchar();
	} while(c!=97);
	erase();
	AffichageCarte();
	refresh();
	PokemonAleatoire->ActualHp =VieAvantCombatEnnemi;
	Player->pokemon1->ActualHp =VieAvantCombatAllie;
	//SuppressionPokemon(PokemonAleatoire);
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
			Player->pokemon1=CopiePokemon(RecherchePokemonStat(ListePokemon,1));
			break;
			case 50:
			Player->pokemon1=CopiePokemon(RecherchePokemonStat(ListePokemon,3));
			break;
			case 51:
			Player->pokemon1=CopiePokemon(RecherchePokemonStat(ListePokemon,5));
			break;
		}
	}while((Touche!=49)&&(Touche!=50)&&(Touche!=51));
	mvprintw(LINES/2-10,COLS/2,"%d",Player->pokemon1->xpNextLevel);
	refresh();
	sleep(1);
	AssociationAttaqueAPokemon(ArbreAtt,Player->pokemon1);
	return Player;
}

void RencontreAleatoire(Joueur *Player,NodePokemon *ListePokemon,NodeAtt *ArbreAtt){
	int Rencontre,PokemonAleatoire;
	Pokemon *PokemonRandom;
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
			PokemonRandom=CopiePokemon(RecherchePokemonStat(ListePokemon,PokemonAleatoire));
			AssociationAttaqueAPokemon(ArbreAtt,PokemonRandom);
			CombatNature(Player,PokemonRandom);
		}
}

void EcritureSauvegarde(Joueur *Player){
	FILE *fichier=NULL;
	fichier=fopen("Sauvegarde.txt","w");
	fprintf(fichier,"%ld ",Player->pokemon1->Number);
	fprintf(fichier,"%ld ",Player->pokemon1->Level);
	fprintf(fichier,"%d ",Player->pokemon1->Attaques[0]->Number);
	fprintf(fichier,"%d ",Player->pokemon1->Attaques[1]->Number);
	fprintf(fichier,"%d ",Player->pokemon1->ActualHp);
	fprintf(fichier,"%ld ",Player->pokemon1->ActualXp);
	fprintf(fichier,"%ld ",Player->pokemon1->att);
	fprintf(fichier,"%ld ",Player->pokemon1->def);
	fprintf(fichier,"%ld ",Player->pokemon1->hp);
	fprintf(fichier,"%ld ",Player->pokemon1->speed);
	fprintf(fichier,"%d ",Player->pokemon1->xpNextLevel);
	fprintf(fichier,"%d ",Player->PositionX);
	fprintf(fichier,"%d ",Player->PositionY);
	fprintf(fichier,"%d ",Player->Argent);
	fprintf(fichier,"%s",Player->pokemon1->Name);
	fclose(fichier);
}

Joueur *LectureSauvegarde(NodeAtt *ArbreAtt){
	FILE *fichier=NULL;
	fichier=fopen("Sauvegarde.txt","r");
	Joueur *Player=(Joueur*)malloc(sizeof(Joueur));
	Pokemon *PokemonActuel=(Pokemon*)malloc(sizeof(Pokemon));
	Player->pokemon1=PokemonActuel;
	att *Attaques0=(att*)malloc(sizeof(att));
	Player->pokemon1->Attaques[0]=Attaques0;
	att *Attaques1=(att*)malloc(sizeof(att));
	Player->pokemon1->Attaques[1]=Attaques1;
	fscanf(fichier,"%ld",&(Player->pokemon1->Number));
	fscanf(fichier,"%ld",&(Player->pokemon1->Level));
	fscanf(fichier,"%d",&(Player->pokemon1->Attaques[0]->Number));
	fscanf(fichier,"%d",&(Player->pokemon1->Attaques[1]->Number));
	fscanf(fichier,"%d",&(Player->pokemon1->ActualHp));
	fscanf(fichier,"%ld",&(Player->pokemon1->ActualXp));
	fscanf(fichier,"%ld",&(Player->pokemon1->att));
	fscanf(fichier,"%ld",&(Player->pokemon1->def));
	fscanf(fichier,"%ld",&(Player->pokemon1->hp));
	fscanf(fichier,"%ld",&(Player->pokemon1->speed));
	fscanf(fichier,"%d",&(Player->pokemon1->xpNextLevel));
	fscanf(fichier,"%d",&(Player->PositionX));
	fscanf(fichier,"%d",&(Player->PositionY));
	fscanf(fichier,"%d",&(Player->Argent));
	fgets(Player->pokemon1->Name,14,fichier);
	AssociationAttaqueAPokemon(ArbreAtt,Player->pokemon1);
	AssociationAttaqueAPokemon(ArbreAtt,Player->pokemon1);
	fclose(fichier);
	return Player;
}

int main(){
	srand(time(NULL));
	int ChoixPartie,ch,posX,posY,PokemonAleatoire=0,Rencontre=0,Clavier=0;
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
		posX=48;posY=38;
	}
	else{
		Player=LectureSauvegarde(ListeAttaques);
		posX=Player->PositionX;
		posY=Player->PositionY;
	}
	sleep(1);
	system("clear");
	erase();
	AffichageCarte();
	mvprintw(posY,posX,"#");
	refresh();
//#########################Boucle principale de jeu#########################################
	do {
			mvprintw(29,75,"Utilisez les touches directionnels pour vous deplacez");
			mvprintw(30,75,"Press f3 pour avoir le menu");
			refresh();
	    if( (ch ==KEY_LEFT)||(ch ==KEY_RIGHT)||(ch ==KEY_UP)||(ch ==KEY_DOWN)){
				Deplacement(ch,&posY,&posX);
				Player->PositionX=posX;
				Player->PositionY=posY;
	    }
			refresh();
			if ((posX<=49)&&(posX>=30)&&(posY<=20)&&(posY>=16)||((posX<=49)&&(posX>=41)&&(posY<=29)&&(posY>=20))){
				RencontreAleatoire(Player,ListePokemon,ListeAttaques);
			}

			if ((ch = getch()) == KEY_F(3)) {
				mvprintw(10,73,"1:Afficher liste pokemon");
				mvprintw(11,73,"2:Afficher profil");
				mvprintw(12,73,"3:Sauvegarder");
				mvprintw(13,73,"4:Quitter le jeu");
				mvprintw(14,73,"5:Sortir");
				do {
					Clavier=getch()-48;
				} while(Clavier!=1&&Clavier!=2&&Clavier!=3&&Clavier!=4&&Clavier!=5);
				switch (Clavier){
					case 1:
						move(1,1);
						system("clear");
						OrdrePokemon(ListePokemon);
						while(getch()!='a');
						break;
					case 2:
						move(1,1);
						system("clear");
						StatPlayer(Player);
						while(getch()!='a');
						break;
					case 3:
						break;
						EcritureSauvegarde(Player);
					case 4:
						break;
					case 5:
						break;
				}
				system("clear");
				erase();
				AffichageCarte();
				mvprintw(posY,posX,"#");
				refresh();
			}
	} while(Clavier!=4);
//##########################################################################################
	endwin();
  DestructionTotal(ListePokemon);
	free(test);
	fclose(fichier);
	SuppressionPlayer(Player);
  return 0;
}
