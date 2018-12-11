/* #include <graph.h> */

#ifndef FUNCTION_H
#define FUNCTION_H

typedef couleur _c;

void            gbegin       ();
void            gclose       ();
int             ginitWindow  (int, int, int, int);
void            gscreen      (int);
void            gchoose      (_c);
void            gclear       (_c);
_c              gcolor       (char*);
_c              grgb         (unsigned char, unsigned char, unsigned char);
void            gpixel       (int, int);
void            gseg         (int, int, int, int);
void            grect        (int, int, int, int);
void            gfillRect    (int, int, int, int);
void            garc         (int, int, int, int, int, int);
void            gfillArc     (int, int, int, int, int, int);
void            gfillTr      (int, int, int, int, int, int);
void            gcopy        (int, int, int, int, int, int, int, int);
void            gwrite       (int, int, char*, int);
int             gtopFontSize (int);
int             gbotFontSize (int);
int             gstrSize     (char*, int);
void            gloadImg     (char*, int, int, int, int, int, int);
void            gbgImg       (char*);
void            gsaveImg     (char*, int, int, int, int);
int             gloadSpr     (char*);
void            gdispSpr     (int, int, int);
void            gfreeSpr     (int);
int             ggetKey      ();
int             gdoKey       ();
void            ggetPos      (void);
int             gdoClick     ();
unsigned long   gms          ();

#endif /* FUNCTION_H */