void EgaliteEntreTableau(char Destination[14],char Origine[14]);
void viderBuffer();
void ncurses_initialiser();
void ModificationName(char Name[14]);
void OrdreAtt(NodeAtt *noeud);
void OrdrePokemon(NodePokemon *PokemonActuel);
void EcriturePositionImpossible(int NumeroPosition,int y,int x);
void StatPlayer(Joueur *Player);

void EcriturePositionImpossible(int NumeroPosition,int y,int x){
	FILE *fichier=fopen("PositionImpossible.txt","a");
	fprintf(fichier,"%d ",NumeroPosition);
	fprintf(fichier,"%d ",x);
	fprintf(fichier,"%d ",y);
	fclose(fichier);
}

void StatPlayer(Joueur *Player){
  printw("%d ",Player->pokemon1->Number);
  printw("Nom du pokemon:%s ",Player->pokemon1->Name);
  printw("Level:%d ",Player->pokemon1->Level);
  printw("Xp Actuel:%d ",Player->pokemon1->ActualXp);
  printw("%d ",Player->PositionX);
  printw("%d",Player->PositionY);
  refresh();
}

void OrdrePokemon(NodePokemon *PokemonActuel){
  if (PokemonActuel!=NULL){
			OrdrePokemon(PokemonActuel->LeftSon);
			printw("%ld ",PokemonActuel->Actuel->Number);
			printw("%s ",PokemonActuel->Actuel->Name);
			printw("%ld ",PokemonActuel->Actuel->att);
			printw("%ld ",PokemonActuel->Actuel->def);
			printw("%ld\n",PokemonActuel->Actuel->hp);
      refresh();
      sleep(1);
			OrdrePokemon(PokemonActuel->RightSon);
  }
}

void OrdreAtt(NodeAtt *noeud){
  if (noeud!=NULL){
			OrdreAtt((*noeud).LeftSon);
			printf("%d\t",noeud->Actuel->Number);
			printf("%d\t",noeud->Actuel->Dommage);
			printf("%s\t",noeud->Actuel->Name );
      printf("\n");
			OrdreAtt((*noeud).RightSon);
  }
}

void ModificationName(char Name[14]){
	for (size_t i = 0; i < 14; i++) {
		if(Name[i]==10) Name[i]='\0';
	}
}

void EgaliteEntreTableau(char Destination[14],char Origine[14]){
	for (size_t i = 0; i < 14; i++) {
		Destination[i]=Origine[i];
	}
}

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void ncurses_initialiser() {
  initscr();	        /* Demarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Desactive l'affichage des caracteres saisis */
  keypad(stdscr, TRUE);	/* Active les touches specifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}
