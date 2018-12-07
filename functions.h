/* #include <graph.h> */

#ifndef FUNCTION_H
#define FUNCTION_H

typedef couleur _c;

void            begin       ();
void            close       ();
int             initWindow  (int, int, int, int);
void            screen      (int);
void            choose      (_c);
void            clear       (_c);
_c              color       (char*);
_c              rgb         (unsigned char, unsigned char, unsigned char);
void            pixel       (int, int);
void            seg         (int, int, int, int);
void            rect        (int, int, int, int);
void            fillRect    (int, int, int, int);
void            arc         (int, int, int, int, int, int);
void            fillArc     (int, int, int, int, int, int);
void            fillTr      (int, int, int, int, int, int);
void            copy        (int, int, int, int, int, int, int, int);
void            write       (int, int, char*, int);
int             topFontSize (int);
int             botFontSize (int);
int             strSize     (char*, int);
void            loadImg     (char*, int, int, int, int, int, int);
void            bgImg       (char*);
void            saveImg     (char*, int, int, int, int);
int             loadSpr     (char*);
void            dispSpr     (int, int, int);
void            freeSpr     (int);
int             getKey      ();
int             doKey       ();
void            getPos      (void);
int             doClick     ();
unsigned long   ms          ();

#endif /* FUNCTION_H */