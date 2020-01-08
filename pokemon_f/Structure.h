#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct NodePokemon NodePokemon;
typedef struct NodeAtt NodeAtt;
typedef struct Pokemon Pokemon;
typedef struct Joueur Joueur;
typedef struct att att;
typedef struct File ElementFile;
typedef struct ControleFile ControleFile;

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
	Pokemon *pokemon[2];
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
  int xpNextLevel;
	att *Attaques[4];
};

struct File
{
	int PosX;
	int PosY;
	ElementFile *ElementSuivant;
};

struct ControleFile
{
	ElementFile *PremierElement;
	int NombreDePosition;
};
