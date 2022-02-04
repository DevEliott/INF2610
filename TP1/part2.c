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
    int childCount = 0;
    // Level 0
    registerProc(0, 0, getpid(), getppid());
    if (fork() == 0)
    {
        // Level 1.1
        registerProc(1, 1, getpid(), getppid());
        if (fork() == 0)
        {
            // Level 2.1
            registerProc(2, 1, getpid(), getppid());
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.2
            registerProc(2, 2, getpid(), getppid());
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.3
            registerProc(2, 3, getpid(), getppid());
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.4
            registerProc(2, 4, getpid(), getppid());
            _exit(EXIT_SUCCESS);
        }
        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
        childCount = 4;
        _exit(childCount + 1);
    }
    if (fork() == 0)
    {
        // Level 1.2
        registerProc(1, 2, getpid(), getppid());
        if (fork() == 0)
        {
            // Level 2.5
            registerProc(2, 5, getpid(), getppid());
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.6
            registerProc(2, 6, getpid(), getppid());
            _exit(EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            // Level 2.7
            registerProc(2, 7, getpid(), getppid());
            _exit(EXIT_SUCCESS);
        }
        wait(NULL);
        wait(NULL);
        wait(NULL);
        childCount = 3;
        _exit(childCount + 1);
    }
    int level1_1, level1_2;
    wait(&level1_1);
    wait(&level1_2);
    childCount += WEXITSTATUS(level1_1) + WEXITSTATUS(level1_2);
    printf("Child count: %d\n", childCount);
    printProcRegistrations();
    execlp("ls", "ls", "-l", NULL);
}
