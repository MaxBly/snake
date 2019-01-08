
#ifndef MENU_H
#define MENU_H

typedef struct Options Options;
struct Options {
    int in_game;
    int in_menu;
    int width;
    int height;
    int window_width;
    int window_height;
    int grid;
    int running;
    int cycle;
    int apples;
    int snake;
};


Options* initOptions(Options*, int, int, int, int, int, int);
int menu();

#endif /* MENU_H */