#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "game.h"
#include "main.h"

void ggrid(int w, int h, int c, int r, _c color) {
    gchoose(color); // on choisit la couleur
    for(int i = 1; i <= c; i++) { // pour chacune des colones c;
        gseg(w/c*i, 0, w/c*i, h); //on divise la largeur de la fenetre par le nb de colone (GRID) que l'on multiplie par la colone désirer

    }
    for (int j = 1; j <= r; j++) {
        gseg(0, h/r*j, w, h/r*j);
    }
}

int ggetCoords(int wh, int grid, int k) { return wh/(wh/grid)*k; } // permet de recuperer les coodronné graphique a partir de la HEIGT/WIDTH, du coef GRID et de la case k

void ghead(int x, int y, _c c) {
    int xx = ggetCoords(WIDTH, GRID, x);
    int yy = ggetCoords(HEIGHT, GRID, y);
    gchoose(c);
    gfillRect(xx, yy, GRID, GRID);
}