#include <graph.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "main.h"
#include "game.h"
#include "menu.h"



Options* initOptions(Options* ops, int width, int height, int grid, int cycle, int apples, int snake) {
    ops = (Options*) malloc(sizeof(Options));
    ops->width = width;
    ops->height = height;
    ops->grid = grid;
    ops->cycle = cycle;
    ops->fps = FPS;
    ops->in_game = 0;
    ops->in_menu = 1;
    ops->in_opts = 0;
    ops->running = 1;
    ops->apples = apples;
    ops->snake = snake;
    ops->center_x = ops->width/ops->grid/2;
    ops->center_y = ops->height/ops->grid/2;
    return ops;
}


void btn (int p, char* text, _c c, _c c2, int sel) {
    int ww = WINDOW_WIDTH;
    int wh = WINDOW_HEIGHT;
    int w = ww/4;
    int h = wh/9;
    int x = 3 * ww / 8;
    int y = p * wh / 9;
    int s = 2;
    gchoose(c);
    gfillRect(x, y, w, h);
    gchoose(c2);
    if (sel) {
        gchoose(grgb(255, 255, 255));
        grect(x, y, w, h);
    }
    gwrite(2 * w - gstrSize(text, s)/2, (p + 0.5) * h - (gtopFontSize(s) + gbotFontSize(s)) / 2, text, s);
}

void btnScroll (int p, char* t, int n, _c c, _c c2, int sel) {
    char text[30];
    int ww = WINDOW_WIDTH;
    int wh = WINDOW_HEIGHT;
    int w = ww/4;
    int h = wh/18;
    int x = 6 * ww / 16;
    int y = p * wh / 18;
    int s = 2;
    gchoose(c);
    gfillRect(x, y, w, h);
    gchoose(c2);
    if (sel) {
        gchoose(grgb(255, 255, 255));
        grect(x, y, w, h);
    }
    sprintf(text, "< %s %d >", t, n);
    gwrite(2 * w - gstrSize(text, s)/2, (p + 0.75) * h - (gtopFontSize(s) + gbotFontSize(s)) / 2, text, s);
}
