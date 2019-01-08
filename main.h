
#ifndef MAIN_H
#define MAIN_H

#include "game.h"

#ifndef     WIDTH
#define     WIDTH   900 // largeur de la fenetre
#endif   /* WIDTH */

#ifndef     HEIGHT
#define     HEIGHT  600 // hauteur
#endif   /* HEIGHT */

#ifndef     WINDOW_WIDTH
#define     WINDOW_WIDTH   1600 // largeur de la fenetre
#endif   /* WINDOW_WIDTH */

#ifndef     WINDOW_HEIGHT
#define     WINDOW_HEIGHT  900 // hauteur
#endif   /* WINDOW_HEIGHT */

#ifndef     GRID
#define     GRID    20  // taille de la grille (unité arbitraire / quotient)
#endif   /* GRID */

#ifndef     SNAKE
#define     SNAKE    10
#endif   /* SNAKE */

#ifndef     APPLES
#define     APPLES    5
#endif   /* APPLES */

#ifndef     CYCLE
#define     CYCLE   100000L // vitesse de recharge du snake
#endif   /* CYCLE */

#ifndef     FRAMERATE
#define     FRAMERATE   60/24 // vitesse de recharge du snake
#endif   /* FRAMERATE */


#define     DEBUG
#endif      /* MAIN_H */