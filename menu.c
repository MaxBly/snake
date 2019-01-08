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
    ops->in_game = 0;
    ops->in_menu = 1;
    ops->running = 1;
    ops->apples = apples;
    ops->snake = snake;

    return ops;
}



int menu () {


    return 0;
}