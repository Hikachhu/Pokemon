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
  }else{
    printf("NULL\n");
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
    printf("%p\n",Nouveau);
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
    printf("%ld,%ld\n",test->Number,test->Level);
    printf("%p,%p\n",ListePokemon,test);
    ListePokemon=Ajout(ListePokemon,test);
    printf("NULL?=%p\n",ListePokemon);
    Ordre(ListePokemon);
  }
  Ordre(ListePokemon);
  printf("Fin Affichage");
  DestructionTotal(ListePokemon);
  fclose(fichier);
  return 0;
}
