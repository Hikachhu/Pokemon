#include "All_Include.h"

void OrdrePokemon(NodePokemon *noeud){
  if (noeud!=NULL){
			OrdrePokemon((*noeud).LeftSon);
			printf("%ld\t",noeud->Actuel->Number);
			printf("%ld\t",noeud->Actuel->Level);
			printf("%ld\t",noeud->Actuel->hp);
			printf("%ld\t",noeud->Actuel->att);
			printf("%ld\t",noeud->Actuel->def);
			printf("%ld\t",noeud->Actuel->speed);
			printf("%s\t",noeud->Actuel->Name);
      printf("\n");
			OrdrePokemon((*noeud).RightSon);
  }
}

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

void AssociationAttaqueAPokemon(NodeAtt *ArbreAtt,Pokemon *pokemon){
	pokemon->Attaques[0]=RechercheAttaquesStat(ArbreAtt,pokemon->Attaques[0]->Number);
	pokemon->Attaques[1]=RechercheAttaquesStat(ArbreAtt,pokemon->Attaques[1]->Number);
}
