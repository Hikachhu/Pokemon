#include "All_Include.h"

NodeAtt *AjoutAttaque(NodeAtt *Noeud,att *attaques){
  NodeAtt *Nouveau=NULL;
  if (Noeud==NULL){
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

NodePokemon *AjoutPokemon(NodePokemon *Noeud,Pokemon *pokemon){
  NodePokemon *Nouveau=NULL;
  if (Noeud==NULL){
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

att *RechercheAttaquesStat(NodeAtt *AttaqueActuel,int numero){
  att *Aretourner=NULL;
	if (AttaqueActuel==NULL){
		return 0;
	}
	else if((AttaqueActuel->Actuel->Number)==numero){
		Aretourner=(AttaqueActuel->Actuel);
	}
	else
	{
		if((AttaqueActuel->Actuel->Number)>numero){
			Aretourner= RechercheAttaquesStat((*AttaqueActuel).LeftSon,numero);
		}
		if((AttaqueActuel->Actuel->Number)<numero){
			Aretourner= RechercheAttaquesStat((*AttaqueActuel).RightSon,numero);
		}
	}
  return Aretourner;
}

Pokemon *RecherchePokemonStat(NodePokemon *PokemonActuel,int numero){
  Pokemon *Aretourner=NULL;
	if (PokemonActuel==NULL){

	}
	else if((PokemonActuel->Actuel->Number)==numero){
		Aretourner= (PokemonActuel->Actuel);
	}
	else
	{
		if((PokemonActuel->Actuel->Number)>numero){
			Aretourner= RecherchePokemonStat((*PokemonActuel).LeftSon,numero);
		}
		if((PokemonActuel->Actuel->Number)<numero){
			Aretourner= RecherchePokemonStat((*PokemonActuel).RightSon,numero);
		}
	}
  return Aretourner;
}

void DestructionTotalAtt(NodeAtt *AttActuel){
	if(AttActuel!=NULL){
		DestructionTotalAtt(AttActuel->LeftSon);
		DestructionTotalAtt(AttActuel->RightSon);
		AttActuel->LeftSon=NULL;
		AttActuel->RightSon=NULL;
		free(AttActuel->Actuel);
		AttActuel->Actuel=NULL;
		free(AttActuel);
	}
}

void DestructionTotal(NodePokemon *Actuel){
	if(Actuel!=NULL){
		DestructionTotal((*Actuel).LeftSon);
		DestructionTotal((*Actuel).RightSon);
		(*Actuel).LeftSon=NULL;
		(*Actuel).RightSon=NULL;
		free(Actuel->Actuel->Attaques[0]);
		Actuel->Actuel->Attaques[0]=NULL;
		free(Actuel->Actuel->Attaques[1]);
		Actuel->Actuel->Attaques[1]=NULL;
		free(Actuel->Actuel);
		Actuel->Actuel=NULL;
		free(Actuel);
	}
}
