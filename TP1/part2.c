/*
 * processlab - part2.c
 *
 * Ecole polytechnique de Montreal,Hiver  2022
 * vos noms, prénoms et matricules
 */

#include "libprocesslab/libprocesslab.h"

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------

// -------------------------------------------------

void question2()
{
    // Level 0
    if (fork() == 0)
    {
        // Level 1.1
        if (fork() == 0)
        {
            // Level 2.1
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.2
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.3
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.4
            _exit(EXIT_SUCCESS);
        }
        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
        _exit(EXIT_SUCCESS);
    }
    if (fork() == 0)
    {
        // Level 1.2
        if (fork() == 0)
        {
            // Level 2.5
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.6
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.7
            _exit(EXIT_SUCCESS);
        }
        wait(NULL);
        wait(NULL);
        wait(NULL);
        _exit(EXIT_SUCCESS);
    }
    wait(NULL);
    wait(NULL);
}
