#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

void            gbegin       (void) {                                                            InitialiserGraphique();}
int             ginitWindow  (int x, int y, int w, int h) {                               return CreerFenetre(x, y, w, h);}
void            gscreen      (int n) {                                                           ChoisirEcran(n);}
void            gclose       (void) {                                                            FermerGraphique();}
void            gchoose      (col c) {                                                           ChoisirCouleurDessin(c);}
void            gclear       (col c) {                                                           EffacerEcran(c);}
col             gcolor       (char *n) {                                                  return CouleurParNom(n);}
col             grgb         (unsigned char r, unsigned char g, unsigned char b) {        return CouleurParComposante(r, g, b);}
void            gpixel       (int x, int y) {                                                    DessinerPixel(x, y);}
void            gseg         (int x, int y, int xx, int yy) {                                    DessinerSegment(x, y, xx, yy);}
void            grect        (int x, int y, int w, int h) {                                      DessinerRectangle(x, y, w, h);}
void            gfillRect    (int x, int y, int w, int h) {                                      RemplirRectangle(x, y, w, h);}
void            garc         (int x, int y, int w, int h, int a1, int a2) {                      DessinerArc(x, y, w, h, a1, a2);}
void            gfillArc     (int x, int y, int w, int h, int a1, int a2) {                      RemplirArc(x, y, w, h, a1, a2);}
void            gfillTr      (int x, int y, int xx, int yy, int xxx, int yyy) {                  RemplirTriangle(x, y, xx, yy, xxx, yyy);}
void            gcopy        (int src, int dst, int ox, int oy, int w, int h, int dx, int dy) {  CopierZone(src, dst, ox, oy, w, h, dx, dy);}
void            gwrite       (int x, int y, char *txt, int t) {                                  EcrireTexte(x, y, txt, t);}
int             gtopFontSize (int t) {                                                    return TailleSupPolice(t);}
int             gbotFontSize (int t) {                                                    return TailleInfPolice(t);}
int             gstrSize     (char *txt, int t) {                                         return TailleChaineEcran(txt, t);}
void            gloadImg     (char *f, int x, int y, int xx, int yy, int w, int h) {             ChargerImage(f, x, y, xx, yy, w, h);}
void            gbgImg       (char *f) {                                                         ChargerImageFond(f);}
int             gloadSpr     (char *f) {                                                  return ChargerSprite(f);}
void            gdispSpr     (int spr, int x, int y) {                                           AfficherSprite(spr, x, y);}
void            gfreeSpr     (int spr) {                                                         LibererSprite(spr);}
int             ggetKey      () {                                                         return Touche();}
int             gdoKey       () {                                                         return ToucheEnAttente();}
void            ggetPos      (void) {                                                            SourisPosition();}
int             gdoClick     () {                                                                SourisCliquee();}
unsigned long   gms          () {                                                         return Microsecondes();}


