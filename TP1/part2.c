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
    // pid_t level0, level1_1, level1_2, level2_1, level2_2, level2_3, level2_4, level2_5, level2_6, level2_7;
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
            _exit(1);
        }
        if (fork() == 0)
        {
            // Level 2.2
            registerProc(2, 2, getpid(), getppid());
            _exit(1);
        }
        if (fork() == 0)
        {
            // Level 2.3
            registerProc(2, 3, getpid(), getppid());
            _exit(1);
        }
        if (fork() == 0)
        {
            // Level 2.4
            registerProc(2, 4, getpid(), getppid());
            _exit(1);
        }
        int level2_1, level2_2, level2_3, level2_4;
        wait(&level2_1);
        wait(&level2_2);
        wait(&level2_3);
        wait(&level2_4);
        printf("Level 2.1: %d\n", WEXITSTATUS(level2_1));
        printf("Level 2.2: %d\n", WEXITSTATUS(level2_2));
        printf("Level 2.3: %d\n", WEXITSTATUS(level2_3));
        printf("Level 2.4: %d\n", WEXITSTATUS(level2_4));
        childCount += WEXITSTATUS(level2_1) + WEXITSTATUS(level2_2) + WEXITSTATUS(level2_3) + WEXITSTATUS(level2_4);
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
            _exit(1);
        }
        if (fork() == 0)
        {
            // Level 2.6
            registerProc(2, 6, getpid(), getppid());
            _exit(1);
        }
        if (fork() == 0)
        {
            // Level 2.7
            registerProc(2, 7, getpid(), getppid());
            _exit(1);
        }
        int level2_5, level2_6, level2_7;
        wait(&level2_5);
        wait(&level2_6);
        wait(&level2_7);
        printf("Level 2.5: %d\n", WEXITSTATUS(level2_5));
        printf("Level 2.6: %d\n", WEXITSTATUS(level2_6));
        printf("Level 2.7: %d\n", WEXITSTATUS(level2_7));
        childCount += WEXITSTATUS(level2_5) + WEXITSTATUS(level2_6) + WEXITSTATUS(level2_7);
        _exit(childCount + 1);
    }
    int level1_1, level1_2;
    wait(&level1_1);
    wait(&level1_2);
    printf("Level 1.1: %d\n", WEXITSTATUS(level1_1));
    printf("Level 1.2: %d\n", WEXITSTATUS(level1_2));
    childCount += WEXITSTATUS(level1_1) + WEXITSTATUS(level1_2);
    printf("Child count: %d\n", childCount);
    printProcRegistrations();
}
