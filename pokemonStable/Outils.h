void EgaliteEntreTableau(char Destination[14],char Origine[14]);
void viderBuffer();
void ncurses_initialiser();
void ModificationName(char Name[14]);
void OrdreAtt(NodeAtt *noeud);
void OrdrePokemon(NodePokemon *PokemonActuel);
void StatPlayer(Joueur *Player);
void LecturePositionImpossible(ControleFile *TeteDeFile);
void AfficherFile(ControleFile *TeteDeFile);
void AfficherPositionImpossible(ControleFile *TeteDeFile);

void AfficherPositionImpossible(ControleFile *TeteDeFile){
	ElementFile *ElementActuel= TeteDeFile->PremierElement;
	while (ElementActuel != NULL){
		mvprintw(ElementActuel->PosY,ElementActuel->PosX,"#");
		ElementActuel = ElementActuel->ElementSuivant;
	}
	refresh();
}

int VerificationMur(ControleFile *TeteDeFile,int ch,int posX,int posY){
	ElementFile *ElementActuel= TeteDeFile->PremierElement;
	int PosYAVerifier=posY,PosXAVerifier=posX;
	switch(ch) {
		case KEY_LEFT:
				PosXAVerifier--;
				break;
		case KEY_RIGHT:
				PosXAVerifier++;
				break;
		case KEY_UP:
				PosYAVerifier--;
				break;
		case KEY_DOWN:
				PosYAVerifier++;
				break;
	}
	mvprintw(40,73,"Futur position A verifier x:%d y:%d",PosXAVerifier,PosYAVerifier);
	while (ElementActuel != NULL){
		if(PosYAVerifier==ElementActuel->PosY && PosXAVerifier==ElementActuel->PosX)
			return 0;
		ElementActuel = ElementActuel->ElementSuivant;
	}
	return 1;
}

void AfficherFile(ControleFile *TeteDeFile){
    ElementFile *ElementActuel= TeteDeFile->PremierElement;
		move(0,0);

    while (ElementActuel != NULL){
			printw("%d:", ElementActuel->PosX);
			printw("%d\t", ElementActuel->PosY);
			ElementActuel = ElementActuel->ElementSuivant;
    }
		refresh();
}

ControleFile *InitialisationFile() {
	ControleFile *TeteDeFile=(ControleFile*)malloc(sizeof(ControleFile));
	TeteDeFile->NombreDePosition=0;
	TeteDeFile->PremierElement=NULL;
	return TeteDeFile;
}

void AjoutDansFile(ControleFile *TeteDeFile,int NumeroPosition,int PositionX,int PositionY){
    ElementFile *Nouveau = malloc(sizeof(*Nouveau));

		Nouveau->NumeroPosition = NumeroPosition;
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
	int PositionX,PositionY,NumeroPosition;
	fichier=fopen("PositionImpossible.txt","r");
	fscanf(fichier,"%d",&(NombreDePosition));
	while(!feof(fichier)){
		fscanf(fichier,"%d",&(PositionY));
		fscanf(fichier,"%d",&(PositionX));
		AjoutDansFile(TeteDeFile,NumeroPosition,PositionX,PositionY);
	}
	fclose(fichier);
}

void StatPlayer(Joueur *Player){
  printw("%d ",Player->pokemon[0]->Number);
  printw("Nom du pokemon:%s ",Player->pokemon[0]->Name);
  printw("Level:%d ",Player->pokemon[0]->Level);
  printw("Xp Actuel:%d ",Player->pokemon[0]->ActualXp);
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
    while (c != '\n' && c != EOF){
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
