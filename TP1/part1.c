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
    const char printfMsg[] = "75dbcb01f571f1c32e196c3a7d27f62e (printed using printf)";
    const char writeMsg[] = "75dbcb01f571f1c32e196c3a7d27f62e (printed using write)\n";
    if (choix == 1)
    {
        for (int i = 0; i < strlen(printfMsg); i++)
        {
            char c = printfMsg[i];
            printf("%c", c);
        }
        write(1, writeMsg, strlen(writeMsg));
        printf("\n");
    }
    else if (choix == 2)
    {
        FILE *file = fopen("./output2.txt", "w");
        if (file == NULL)
        {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        if (setvbuf(file, NULL, _IONBF, BUFSIZ) != 0)
        {
            perror("setvbuf failed");
            exit(EXIT_FAILURE);
        }
        printf("%s", printfMsg);
        // setvbuf(file, NULL, _IONBF, BUFSIZ);
        write(1, writeMsg, strlen(writeMsg));
        fclose(file);
    }
}
