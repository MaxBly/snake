
typedef struct Coords Coords;

struct Coords {
    int x;
    int y;
};

struct List {
    int n;
    Coords *Coords;
};

#ifndef     HEIGHT
#define     HEIGHT  450 // hauteur
#endif   /* HEIGHT */

#ifndef     WIDTH
#define     WIDTH   600 // largeur de la fenetre
#endif   /* WIDTH */

#ifndef     GRID
#define     GRID    15  // taille de la grille (unité arbitraire / quotient)
#endif   /* GRID */

#define     DEBUG