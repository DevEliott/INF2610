/*
 *  part1.c
 *
 * ajoutez vos noms, prénoms, matricules et votre section de laboratoire
 */

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------
#include <stdio.h>
// -------------------------------------------------

#include "./libprocesslab/libprocesslab.h"

void question1(int choix)
{
    printf("75dbcb01f571f1c32e196c3a7d27f62e (printed using printf)");
    const char writeMsg[] = "75dbcb01f571f1c32e196c3a7d27f62e (printed using write)\n";
    write(1, writeMsg, sizeof(writeMsg));
    printf("\n");
}
