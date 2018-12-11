#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "game.h"

void ggrid(int w, int h, int c, int r, _c color) {
    gchoose(color);
    for(int i = 1; i <= c; i++) {
        gseg(w/c*i, 0, w/c*i, h);
    }
    for (int j = 1; j <= r; j++) {
        gseg(0, h/r*j, w, h/r*j);
    }
}

int ggetCoords(int wh, int grid, int k) { return wh/(wh/grid)*k; }