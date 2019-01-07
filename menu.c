#include <stdlib.h>
#include <graph.h>
#include <stdio.h>
#include "functions.h"
#include "main.h"

int main () { 
    gbegin ();
    ginitWindow (100,2100,WIDTH,HEIGHT);
    gclear(grgb(45,45,45));

    
    gwrite(20,600,"Quitter",2);
    gcolor("white");
    /* Je voulais juste voir si ça fonctionne. Truc tout simple. */
    return 0;
}