#include "All_Include.h"

void Defiler(ControleFile *TeteDeFile){
    if (TeteDeFile->PremierElement != NULL){
        ElementFile *ElementDeFile = TeteDeFile->PremierElement;
        TeteDeFile->PremierElement = ElementDeFile->ElementSuivant;
        free(ElementDeFile);
    }
}

void DestructionFile(ControleFile *TeteDeFile){
	while(TeteDeFile->PremierElement!=NULL){
		Defiler(TeteDeFile);
	}
}

ControleFile *InitialisationFile(){
	ControleFile *TeteDeFile=(ControleFile*)malloc(sizeof(ControleFile));
	TeteDeFile->NombreDePosition=0;
	TeteDeFile->PremierElement=NULL;
	return TeteDeFile;
}

void AjoutDansFile(ControleFile *TeteDeFile,int PositionX,int PositionY){
    ElementFile *Nouveau = malloc(sizeof(*Nouveau));

		Nouveau->PosX = PositionX;
		Nouveau->PosY = PositionY;
    Nouveau->ElementSuivant = NULL;

    if (TeteDeFile->PremierElement != NULL){
        ElementFile *Actuel=TeteDeFile->PremierElement;
        while (Actuel->ElementSuivant != NULL)
        {
            Actuel=Actuel->ElementSuivant;
        }
        Actuel->ElementSuivant=Nouveau;
    }
    else{
        TeteDeFile->PremierElement=Nouveau;
    }
		TeteDeFile->NombreDePosition++;
}

void LecturePositionImpossible(ControleFile *TeteDeFile){
	FILE *fichier=NULL;
	int NombreDePosition;
	int PositionX,PositionY;
	fichier=fopen("PositionImpossible.txt","r");
	fscanf(fichier,"%d",&(NombreDePosition));
	while(!feof(fichier)){
		fscanf(fichier,"%d",&(PositionY));
		fscanf(fichier,"%d",&(PositionX));
		AjoutDansFile(TeteDeFile,PositionX,PositionY);
	}
	fclose(fichier);
}
