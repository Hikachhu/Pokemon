#include "Structure.h"

void DestructionTotal(NodePokemon *Actuel);
void SuppressionPlayer(Joueur *Player);
void SuppressionPokemon(Pokemon *PokemonCible);

void SuppressionPlayer(Joueur *Player){
	SuppressionPokemon(Player->pokemon1);
	free(Player);
	Player=NULL;
}

void SuppressionPokemon(Pokemon *PokemonCible){
	free(PokemonCible->Attaques[0]);
	PokemonCible->Attaques[0]=NULL;
	free(PokemonCible->Attaques[1]);
	PokemonCible->Attaques[1]=NULL;
	free(PokemonCible);
	PokemonCible=NULL;
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
