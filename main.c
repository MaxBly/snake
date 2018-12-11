#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "game.h"

#define     WIDTH   600
#define     HEIGHT  450
#define     GRID    15

#define     DEBUG

int main(void) {
    gbegin();
    ginitWindow(100,100,WIDTH,HEIGHT);
    gclear(grgb(0,0,0));

    int running = 1;
    int x = 0, y = 0,
        xx = 0, yy = 0;
    //gchoose(grgb(255,0,0));

    while (running) {
        gscreen(1);
        gclear(grgb(0,0,0));
        ggrid(WIDTH, HEIGHT, WIDTH/GRID, HEIGHT/GRID, grgb(255,255,255));
        gchoose(grgb(255,0,0));
        xx = ggetCoords(WIDTH, GRID, x);
        yy = ggetCoords(HEIGHT, GRID, y);
        gfillRect(xx, yy, GRID, GRID);
        #ifdef DEBUG
            printf("[%d|%d][%d|%d]\n", x, xx, y, yy);
        #endif /* DEBUG */




        if (gdoKey()) {
            switch(ggetKey()) {
                case XK_Escape: running = 0; break;
                case XK_Left: if (x>0) x--; break;
                case XK_Right: if (x<WIDTH/GRID-1) x++; break;
                case XK_Down: if (y<HEIGHT/GRID-1) y++; break;
                case XK_Up: if (y>0) y--; break;
            }

        }

        gcopy(1,0,0,0,WIDTH,HEIGHT,0,0);
    }

    return 0;
}
