void AffichageCarte() {
  int PositionImpossible=0;
  for (size_t i = 0; i <= 10; i++) {
    EcriturePositionImpossible(PositionImpossible,1+i,1);
    PositionImpossible++;
  }
	AffichageColonne(10,1,1);
  for (size_t i = 0; i <= 40; i++) {
    EcriturePositionImpossible(PositionImpossible,1,1+i);
    PositionImpossible++;
  }
	AffichageLigne(40,1,1);
  for (size_t i = 0; i <= 10; i++) {
    EcriturePositionImpossible(PositionImpossible,1+i,42);
    PositionImpossible++;
  }
	AffichageColonne(10,1,42);
  for (size_t i = 0; i <= 20; i++) {
    EcriturePositionImpossible(PositionImpossible,11,1+i);
    PositionImpossible++;
  }
	AffichageLigne(20,11,1);
  for (size_t i = 0; i <= 14; i++) {
    EcriturePositionImpossible(PositionImpossible,11,27+i);
    PositionImpossible++;
  }
	AffichageLigne(14,11,27);
  for (size_t i = 0; i <= 10; i++) {
    EcriturePositionImpossible(PositionImpossible,4+i,22);
    PositionImpossible++;
  }
	AffichageColonne(10,4,22);
  for (size_t i = 0; i <= 40; i++) {
    EcriturePositionImpossible(PositionImpossible,24+i,27);
    PositionImpossible++;
  }
	AffichageColonne(4,24,27);
  for (size_t i = 0; i <= 40; i++) {
    EcriturePositionImpossible(PositionImpossible,15,27+i);
    PositionImpossible++;
  }
	AffichageLigne(24,15,27);
  for (size_t i = 0; i <= 16; i++) {
    EcriturePositionImpossible(PositionImpossible,21,22+i);
    PositionImpossible++;
  }
	AffichageLigne(16,21,22);
  for (size_t i = 0; i <= 25; i++) {
    EcriturePositionImpossible(PositionImpossible,15+i,22);
    PositionImpossible++;
  }
	AffichageColonne(25,15,52);
  for (size_t i = 0; i <= 10; i++) {
    EcriturePositionImpossible(PositionImpossible,39+i,21);
    PositionImpossible++;
  }
	AffichageColonne(10,21,39);
  for (size_t i = 0; i <= 20; i++) {
    EcriturePositionImpossible(PositionImpossible,31,18+i);
    PositionImpossible++;
  }
	AffichageLigne(20,31,18);
  for (size_t i = 0; i <= 9; i++) {
    EcriturePositionImpossible(PositionImpossible,31+i,18);
    PositionImpossible++;
  }
	AffichageColonne(9,31,18);
  for (size_t i = 0; i <= 33; i++) {
    EcriturePositionImpossible(PositionImpossible,40,18+i);
    PositionImpossible++;
  }
	AffichageLigne(33,40,18);
  for (size_t i = 0; i <= 4; i++) {
    EcriturePositionImpossible(PositionImpossible,16+i,30);
    PositionImpossible++;
  }

	AffichageColonne(4,16,30);
  for (size_t i = 0; i <= 40; i++) {
    EcriturePositionImpossible(PositionImpossible,18+i,49);
    PositionImpossible++;
  }
	AffichageColonne(4,18,49);
  for (size_t i = 0; i <= 40; i++) {
    EcriturePositionImpossible(PositionImpossible,16,30+i);
    PositionImpossible++;
  }
	AffichageLigne(18,16,30);
  for (size_t i = 0; i <= 10; i++) {
    EcriturePositionImpossible(PositionImpossible,20,30+i);
    PositionImpossible++;
  }
	AffichageLigne(10,20,30);
  for (size_t i = 0; i <= 9; i++) {
    EcriturePositionImpossible(PositionImpossible,20+i,41);
    PositionImpossible++;
  }

	AffichageColonne(9,20,41);
  for (size_t i = 0; i <= 9; i++) {
    EcriturePositionImpossible(PositionImpossible,20+i,49);
    PositionImpossible++;
  }
	AffichageColonne(9,20,49);

  for (size_t i = 0; i <= 7; i++) {
    EcriturePositionImpossible(PositionImpossible,29,41+i);
    PositionImpossible++;
  }
  AffichageLigne(7,29,41);
  for (size_t i = 0; i <= 45; i++) {
    EcriturePositionImpossible(PositionImpossible,0+i,70);
    PositionImpossible++;
  }

	AffichageColonne(45,0,70);

	refresh();
}
