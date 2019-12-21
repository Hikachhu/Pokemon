#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node Node;
typedef struct Pokemon Pokemon;

struct Node{
	Pokemon *Actuel;
	Node *LeftSon;
	Node *RightSon;
};

struct Pokemon{
  size_t Number;
  size_t Level;
  size_t att;
  size_t def;
  size_t hp;
  size_t speed;
  size_t ActualHp;
  size_t ActualXp;
  size_t NumberAtt1;
  size_t NumberAtt2;
  size_t NumberAtt3;
  size_t NumberAtt4;
};

void Ordre(Node *noeud){
  if (noeud!=NULL){
			Ordre((*noeud).LeftSon);
			printf("%ld\t",noeud->Actuel->Number);
			printf("%ld\t",noeud->Actuel->Level);
      printf("\n");
			Ordre((*noeud).RightSon);
  }
}

void DestructionTotal(Node *Actuel){
	if(Actuel!=NULL){
		DestructionTotal((*Actuel).LeftSon);
		DestructionTotal((*Actuel).RightSon);
		(*Actuel).RightSon=NULL;
		(*Actuel).LeftSon=NULL;
		Actuel=NULL;
		free(Actuel);
	}
}

Node *Ajout(Node *Noeud,Pokemon *pokemon) {
  if (Noeud==NULL){
    Node *Nouveau=NULL;
    Nouveau=(Node*)malloc(sizeof(Nouveau));
    printf("%ld,%ld\n",pokemon->Number,pokemon->Level);
    (Nouveau->Actuel)=(pokemon);
    printf("%ld,%ld\n",Nouveau->Actuel->Number,Nouveau->Actuel->Level);
    (*Nouveau).RightSon=NULL;
    (*Nouveau).LeftSon=NULL;
    return Nouveau;
  }
  else{
    if (Noeud->Actuel->Number<pokemon->Number){
      (*Noeud).RightSon=Ajout((*Noeud).RightSon,pokemon);
    }
    else{
      (*Noeud).LeftSon=Ajout((*Noeud).LeftSon,pokemon);
    }
  }
}

Pokemon *LectureListePokemon(FILE *fichier){
  Pokemon *Nouveau;
  Nouveau=(Pokemon*)malloc(sizeof(Nouveau));
  fscanf(fichier,"%ld %ld",&(Nouveau->Number),&(Nouveau->Level));
  return Nouveau;
}

int main() {
  Node *ListePokemon=NULL;
  FILE *fichier=NULL;
  Pokemon *test=NULL;
  fichier=fopen("ListePokemon.txt","r");
  if(fichier==NULL) printf("Erreur ouverture fichier");
  for (size_t i = 1; i <= 31; i++) {
    test=LectureListePokemon(fichier);
    ListePokemon=Ajout(ListePokemon,test);
    printf("Premier pokemon=%ld,%ld\n",ListePokemon->Actuel->Number,ListePokemon->Actuel->Level);
    free(test);printf("Debut Ordre:\n");
    Ordre(ListePokemon);
		printf("Fin Ordre:\n");
  }
  Ordre(ListePokemon);
  DestructionTotal(ListePokemon);
	free(ListePokemon);
  fclose(fichier);
	//test
  return 0;
}
