
#ifndef GAME_H
#define GAME_H

typedef struct List List;
struct List {
    int x;
    int y;
    _c c;
    List* prev;
    List* next;
};

typedef struct Snake Snake;
struct Snake {
    int length;
    int speed;
    int x;
    int y;
    int dir_x;
    int dir_y;
};

typedef struct Garden Garden;
struct Garden {
    int level;
    int r;
    int n;
    List* apples;
};

void    ggrid       (int, int, int, int, _c);
int     ggetCoords  (int, int, int);
double  ggetDist    (int, int, int, int);
void    ghead       (int, int, _c);
_c      wheel       (int);

List*   pushTop (List*, int, int, _c);
List*   pushBot (List*, int, int, _c);
List*   popBot  (List*);
List*   push    (List*, int, int, int, _c);
List*   pop     (List*, int, int, int*);
void    disp    (List*, _c);
void    display (List*, int);
void    dispgar (Garden*);

#endif /* GAME_H */