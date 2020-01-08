#include "All_Include.h"

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
