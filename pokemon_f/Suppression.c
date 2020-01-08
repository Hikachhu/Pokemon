#include "All_Include.h"

void SuppressionPlayer(Joueur *Player){
	SuppressionPokemon(Player->pokemon[0]);
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
