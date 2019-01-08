
#ifndef MENU_H
#define MENU_H

typedef struct Options Options;
struct Options {
    int in_game;
    int in_opts;
    int in_menu;
    int width;
    int height;
    int window_width;
    int window_height;
    int grid;
    int running;
    int cycle;
    int speed;
    int fps;
    int apples;
    int snake;
    int center_x;
    int center_y;
};

Options* initOptions(Options*, int, int, int, int, int, int);
void btn(int, char*, _c, _c, int);
void btnScroll(int, char*, int, _c, _c, int);

#endif /* MENU_H */