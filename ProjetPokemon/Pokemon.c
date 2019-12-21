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

Node *Ajout(Node *Noeud,Pokemon *Actuel) {
  if (Noeud==NULL){
    Node *Nouveau=(Node*)malloc(sizeof(Nouveau));
    Noeud->Actuel=Actuel;
    (*Nouveau).RightSon=NULL;
    (*Nouveau).LeftSon=NULL;
    return Nouveau;
  }
  else{
    if (Noeud->Actuel->Number<Actuel->Number){
      (*Noeud).RightSon=Ajout((*Noeud).RightSon,Actuel);
    }
    else{
      (*Noeud).LeftSon=Ajout((*Noeud).LeftSon,Actuel);
    }
  }
}

Pokemon *LectureListePokemon(FILE *fichier){
  printf("Debug");
  Pokemon *Nouveau;
  fscanf(fichier,"%ld %ld",&(Nouveau->Number),&(Nouveau->Level));
  return Nouveau;
}

int main() {
  printf("debug");
  Node *ListePokemon=NULL;
  FILE *fichier=NULL
  *fichier=fopen("ListePokemon.txt","r");
  if(*fichier==NULL) printf("Erreur ouverture fichier");
  Pokemon *test=LectureListePokemon(fichier);
  printf("Debug");

  //for (size_t i = 1; i <= 31; i++) {
    //printf("%ld:%ld",test->Number,test->Level);
    //Ajout(ListePokemon,);
  //}
  //Ordre(ListePokemon);
  fclose(fichier);
  return 0;
}
