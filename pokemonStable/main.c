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

int CombatNature(Joueur *Player,Pokemon *PokemonAleatoire){
	int AttaqueChoisi=0,DegatPlayer=0,DegatAdversaire=0,AttaqueAleatoire=0,c;
	int VieAvantCombatAllie=Player->pokemon[0]->ActualHp,VieAvantCombatEnnemi=PokemonAleatoire->ActualHp;
	int VieDurantCombatAllie=VieAvantCombatAllie+5*Player->pokemon[0]->Level,VieDurantCombatEnnemi=VieAvantCombatEnnemi+5*PokemonAleatoire->Level;
	int Aretourner;
	mvprintw(9,73,"Pokemon:%s",Player->pokemon[0]->Name);
	mvprintw(9,95,"Attaque 1:%s",Player->pokemon[0]->Attaques[0]->Name);
	mvprintw(10,95,"Attaque 2:%s",Player->pokemon[0]->Attaques[1]->Name);
	mvprintw(11,73,"Experience Actuel:%d/%d",Player->pokemon[0]->ActualXp,(Player->pokemon[0]->xpNextLevel+15*Player->pokemon[0]->Level));
	mvprintw(12,73,"Niveau Actuel:%d",Player->pokemon[0]->Level);

	mvprintw(13,73,"Contre:%s",PokemonAleatoire->Name);
	mvprintw(13,95,"Attaque 1:%s",PokemonAleatoire->Attaques[0]->Name);
	mvprintw(14,95,"Attaque 2:%s",PokemonAleatoire->Attaques[1]->Name);
	mvprintw(15,73,"Niveau Actuel:%d",PokemonAleatoire->Level);
	refresh();
	do{
		mvprintw(17,73,"Attaque 1 ou Attaque 2");
		mvprintw(10,73,"Vie Actuel:   ");
		mvprintw(10,73,"Vie Actuel:%d",VieDurantCombatAllie);
		mvprintw(14,73,"Vie Actuel:   ");
		mvprintw(14,73,"Vie Actuel:%d",VieDurantCombatEnnemi);
		refresh();
		do {
			AttaqueChoisi=getch();
			refresh();
		} while(AttaqueChoisi!=49&&AttaqueChoisi!=50);
		mvprintw(19,73,"Vous avez choisi %s           ",Player->pokemon[0]->Attaques[AttaqueChoisi-49]->Name);
		refresh();
		AttaqueAleatoire=rand()%2;
		DegatPlayer=( (((Player->pokemon[0]->Level)*(4)+2)*(Player->pokemon[0]->Attaques[AttaqueChoisi-49]->Dommage)*((Player->pokemon[0]->att)+Player->pokemon[0]->att)+2)/((PokemonAleatoire->def+PokemonAleatoire->Level)*50) );
		DegatAdversaire=((((PokemonAleatoire->Level)*(4)+2)*(PokemonAleatoire->Attaques[AttaqueAleatoire]->Dommage)*(PokemonAleatoire->att+PokemonAleatoire->Level)+2)/((Player->pokemon[0]->def+Player->pokemon[0]->Level)*50));
		mvprintw(20,73,"Degat au pokemon adversaire:   ",DegatPlayer);
		mvprintw(20,73,"Degat au pokemon adversaire:%d",DegatPlayer);
		mvprintw(21,73,"Degat au pokemon allie:    ",DegatAdversaire);
		mvprintw(21,73,"Degat au pokemon allie:%d",DegatAdversaire);
		refresh();
		VieDurantCombatAllie =(VieDurantCombatAllie-DegatAdversaire);
		VieDurantCombatEnnemi =(VieDurantCombatEnnemi-DegatPlayer);

	}while(((VieDurantCombatAllie)>0)&&((VieDurantCombatEnnemi)>0));
	if (VieDurantCombatEnnemi>0){
		mvprintw(22,73,"Vous avez perdu le combat");
		Aretourner=0;
	}
	else{
		Aretourner=1;
		Player->pokemon[0]->ActualXp+=((Player->pokemon[0]->Level+2)*(PokemonAleatoire->Level+2)+3);
		mvprintw(22,73,"Vous avez gagne");
		if ((Player->pokemon[0]->ActualXp)>=(Player->pokemon[0]->xpNextLevel+(Player->pokemon[0]->Level)*15)){
			Player->pokemon[0]->ActualXp=(Player->pokemon[0]->ActualXp-(Player->pokemon[0]->xpNextLevel+(Player->pokemon[0]->Level)*15));
			(Player->pokemon[0]->Level)++;
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
	Player->pokemon[0]->ActualHp =VieAvantCombatAllie;
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
			Player->pokemon[0]=CopiePokemon(RecherchePokemonStat(ListePokemon,1));
			break;
			case 50:
			Player->pokemon[0]=CopiePokemon(RecherchePokemonStat(ListePokemon,3));
			break;
			case 51:
			Player->pokemon[0]=CopiePokemon(RecherchePokemonStat(ListePokemon,5));
			break;
		}
	}while((Touche!=49)&&(Touche!=50)&&(Touche!=51));
	mvprintw(LINES/2-10,COLS/2,"%d",Player->pokemon[0]->xpNextLevel);
	refresh();
	sleep(1);
	AssociationAttaqueAPokemon(ArbreAtt,Player->pokemon[0]);
	Player->pokemon[1]=(Pokemon*)malloc(sizeof(Pokemon));
	Player->pokemon[2]=(Pokemon*)malloc(sizeof(Pokemon));
	return Player;
}

void RencontreAleatoire(Joueur *Player,NodePokemon *ListePokemon,NodeAtt *ArbreAtt){
	int Rencontre,PokemonAleatoire;
	Pokemon *PokemonRandom;
	Rencontre=rand()%10;
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
			PokemonRandom->Level+=(rand()%(Player->pokemon[0]->Level+2));
			AssociationAttaqueAPokemon(ArbreAtt,PokemonRandom);
			CombatNature(Player,PokemonRandom);
		}
}

void EcritureSauvegarde(Joueur *Player){
	FILE *fichier=NULL;
	fichier=fopen("Sauvegarde.txt","wb");
	mvprintw(10,73,"Sauvegarde en cours");
	fprintf(fichier,"%ld ",Player->pokemon[0]->Number);
	fprintf(fichier,"%ld ",Player->pokemon[0]->Level);
	fprintf(fichier,"%d ",Player->pokemon[0]->Attaques[0]->Number);
	fprintf(fichier,"%d ",Player->pokemon[0]->Attaques[1]->Number);
	fprintf(fichier,"%d ",Player->pokemon[0]->ActualHp);
	fprintf(fichier,"%ld ",Player->pokemon[0]->ActualXp);
	fprintf(fichier,"%ld ",Player->pokemon[0]->att);
	fprintf(fichier,"%ld ",Player->pokemon[0]->def);
	fprintf(fichier,"%ld ",Player->pokemon[0]->hp);
	fprintf(fichier,"%ld ",Player->pokemon[0]->speed);
	fprintf(fichier,"%d ",Player->pokemon[0]->xpNextLevel);
	fprintf(fichier,"%d ",Player->PositionX);
	fprintf(fichier,"%d ",Player->PositionY);
	fprintf(fichier,"%d ",Player->Argent);
	fprintf(fichier,"%s",Player->pokemon[0]->Name);
	fclose(fichier);
	refresh();
	while(getch()!='a');
}

Joueur *LectureSauvegarde(NodeAtt *ArbreAtt){
	FILE *fichier=NULL;
	fichier=fopen("Sauvegarde.txt","r");
	Joueur *Player=(Joueur*)malloc(sizeof(Joueur));
	Pokemon *PokemonActuel=(Pokemon*)malloc(sizeof(Pokemon));
	Player->pokemon[0]=PokemonActuel;
	att *Attaques0=(att*)malloc(sizeof(att));
	Player->pokemon[0]->Attaques[0]=Attaques0;
	att *Attaques1=(att*)malloc(sizeof(att));
	Player->pokemon[0]->Attaques[1]=Attaques1;
	fscanf(fichier,"%ld",&(Player->pokemon[0]->Number));
	fscanf(fichier,"%ld",&(Player->pokemon[0]->Level));
	fscanf(fichier,"%d",&(Player->pokemon[0]->Attaques[0]->Number));
	fscanf(fichier,"%d",&(Player->pokemon[0]->Attaques[1]->Number));
	fscanf(fichier,"%d",&(Player->pokemon[0]->ActualHp));
	fscanf(fichier,"%ld",&(Player->pokemon[0]->ActualXp));
	fscanf(fichier,"%ld",&(Player->pokemon[0]->att));
	fscanf(fichier,"%ld",&(Player->pokemon[0]->def));
	fscanf(fichier,"%ld",&(Player->pokemon[0]->hp));
	fscanf(fichier,"%ld",&(Player->pokemon[0]->speed));
	fscanf(fichier,"%d",&(Player->pokemon[0]->xpNextLevel));
	fscanf(fichier,"%d",&(Player->PositionX));
	fscanf(fichier,"%d",&(Player->PositionY));
	fscanf(fichier,"%d",&(Player->Argent));
	fgets(Player->pokemon[0]->Name,14,fichier);
	AssociationAttaqueAPokemon(ArbreAtt,Player->pokemon[0]);
	AssociationAttaqueAPokemon(ArbreAtt,Player->pokemon[0]);
	fclose(fichier);
	return Player;
}

void CombatArene(Joueur *Player,NodePokemon *ListePokemon,NodeAtt *ArbreAtt){
	Joueur *PlayerAdverse=(Joueur*)malloc(sizeof(Joueur));
	int Reussite=1;
	int ListePokemonAdverse[3]={26,27,31};
	refresh();
	for (int i = 0; i < 3 && Reussite==1 ; i++) {
		if (Reussite==0) break;
		mvprintw(1,73,"Reussite:%d");
		mvprintw(2,73,"Combat numero %d",i);
		refresh();
		PlayerAdverse->pokemon[i]=CopiePokemon(RecherchePokemonStat(ListePokemon,ListePokemonAdverse[i]));
		PlayerAdverse->pokemon[i]->Level=5;
		AssociationAttaqueAPokemon(ArbreAtt,PlayerAdverse->pokemon[i]);
		mvprintw(3,73,"                                  ");
		if(CombatNature(Player,PlayerAdverse->pokemon[i])==0){
			mvprintw(3,73,"                                     ");
			mvprintw(3,73,"Vous avez perdu le combat %d d'arene",i);
			Reussite=0;
		}else{
			Reussite=1;
			mvprintw(3,73,"                                     ");
			mvprintw(3,73,"Vous avez gagne le combat %d d'arene");
		}
		refresh();
	}
	mvprintw(3,73,"                                     ");
	refresh();
}

int main(){
	srand(time(NULL));
	int ChoixPartie,ch,posX,posY,PokemonAleatoire=0,Rencontre=0,Clavier=0;
	ControleFile *TeteDeFile;
	NodePokemon *ListePokemon=NULL;
	NodeAtt *ListeAttaques=NULL;
	FILE *fichier=NULL;
	Pokemon *test=NULL,*PokemonRencontre=NULL;
	att *attaques=NULL;
	Joueur *Player=NULL;
	ncurses_initialiser();
	echo();
	system("clear");
	TeteDeFile=InitialisationFile();
	LecturePositionImpossible(TeteDeFile);
	refresh();
	printf("Voulez-vous démarrer une nouvelle partie ?(1=Nouvelle partie/2=Ancienne partie)");
	scanf("%d",&ChoixPartie);
	printf("Choix=%d\n",ChoixPartie);
	noecho();
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
	fclose(fichier);
	refresh();
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
	mvprintw(29,75,"Utilisez les touches directionnels pour vous deplacez");
	mvprintw(30,75,"Press 'm' pour avoir le menu");
	refresh();
//#########################Boucle principale de jeu#########################################
	do {
			ch=getch();
			mvprintw(29,75,"Utilisez les touches directionnels pour vous deplacez");
			mvprintw(30,75,"Press 'm' pour avoir le menu");
			refresh();
	    if( (ch ==KEY_LEFT)||(ch ==KEY_RIGHT)||(ch ==KEY_UP)||(ch ==KEY_DOWN)){
				if (VerificationMur(TeteDeFile,ch,posX,posY)==1) {
					Deplacement(ch,&posY,&posX);
					Player->PositionX=posX;
					Player->PositionY=posY;
				}
				else{
					mvprintw(5,73,"Position Impossible");
					refresh();
				}
	    }
			refresh();
			if ((posX<=49)&&(posX>=30)&&(posY<=20)&&(posY>=16)||((posX<=49)&&(posX>=41)&&(posY<=29)&&(posY>=20))){
				RencontreAleatoire(Player,ListePokemon,ListeAttaques);
			}
			if (posX==35 && posY==5){
				CombatArene(Player,ListePokemon,ListeAttaques);
			}
			if (ch == 'm') {
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
						EcritureSauvegarde(Player);
						break;
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
	SuppressionPlayer(Player);
	DestructionTotalAtt(ListeAttaques);
  return 0;
}
