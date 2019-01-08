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
    //ops->framerate = FRAMERATE;
    ops->in_game = 0;
    ops->in_menu = 1;
    ops->running = 1;
    ops->apples = apples;
    ops->snake = snake;

    return ops;
}


void btnPlay (_c c, _c c2) {
    int ww = WINDOW_WIDTH;
    int wh = WINDOW_HEIGHT;
    int w = ww/4;
    int h = wh/9;
    int p = 2;
    int x = 3 * ww / 8;
    int y = p * wh / 9;
    int s = 2;
    gchoose(c);
    gfillRect(x, y, w, h);
    gchoose(c2);
    char text[10] = "PLAY";
    gwrite(2 * w - gstrSize(text, s)/2, (p + 0.5) * h - (gtopFontSize(s) + gbotFontSize(s)) / 2, text, s);
}

void btnOpts (_c c, _c c2) {
    int ww = WINDOW_WIDTH;
    int wh = WINDOW_HEIGHT;
    int w = ww/4;
    int h = wh/9;
    int p = 4;
    int x = 3 * ww / 8;
    int y = p * wh / 9;
    int s = 0;
    gchoose(c);
    gfillRect(x, y, w, h);
    gchoose(c2);
    char text[10] = "OPTIONS";
    gwrite(2 * w - gstrSize(text, s)/2, (p + 0.5) * h - (gtopFontSize(s) + gbotFontSize(s)) / 2, text, s);
}

void btnQuit (_c c, _c c2) {
    int ww = WINDOW_WIDTH;
    int wh = WINDOW_HEIGHT;
    int w = ww/4;
    int h = wh/9;
    int p = 6;
    int x = 3 * ww / 8;
    int y = p * wh / 9;
    int s = 2;
    gchoose(c);
    gfillRect(x, y, w, h);
    gchoose(c2);
    char text[10] = "QUIT";
    gwrite(2 * w - gstrSize(text, s)/2,  (p + 0.5) * h - (gtopFontSize(s) + gbotFontSize(s)) / 2, text, s);
}