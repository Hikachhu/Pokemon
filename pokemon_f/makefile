CFLAGS=-Wall -lncursesw
CC=gcc 
OBJS=obj
EXE=Jeu


$(OBJS)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(OBJS)/Outils.o $(OBJS)/OutilListe.o $(OBJS)/OutilSauvegarde.o $(OBJS)/OutilArbre.o $(OBJS)/Suppression.o $(OBJS)/OutilGestionPokemon.o $(OBJS)/AffichageNcurses.o $(OBJS)/main.o
	gcc -o $(EXE) $(OBJS)/Outils.o $(OBJS)/OutilListe.o $(OBJS)/OutilSauvegarde.o $(OBJS)/OutilArbre.o $(OBJS)/Suppression.o $(OBJS)/OutilGestionPokemon.o $(OBJS)/AffichageNcurses.o $(OBJS)/main.o -lncurses
clean:
	rm $(OBJS)/*.o
