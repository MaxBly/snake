
#ifndef GAME_H
#define GAME_H

typedef struct List List;
struct List {
    int x;
    int y;
    List* prev;
    List* next;
};

typedef struct Apple Apple;
struct Apple {
    int x;
    int y;
};

void    ggrid       (int, int, int, int, _c);
int     ggetCoords  (int, int, int);
double  ggetDist    (int, int, int, int);

List*   pushTop (List*, int, int);
List*   pushBot (List*, int, int);
List*   popBot  (List*);
List*   pop     (List*, int, int, int);
void    disp    (List*);

#endif /* GAME_H */