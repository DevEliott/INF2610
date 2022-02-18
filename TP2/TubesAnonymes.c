#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int fd2[2];
    pipe(fd2);
    // Processus P3
    if (fork() == 0)
    {
        // Processus P2
        if (fork() == 0)
        {
            int fd1[2];
            pipe(fd1);
            // Processus P1
            if (fork() == 0)
            {
                int fileIn = open("In.txt", O_RDONLY);
                dup2(fileIn, 0);
                dup2(fd1[0], 1);
                close(fileIn);
                close(fd1[0]);
                close(fd1[1]);
                close(fd2[0]);
                close(fd2[1]);
                execlp("rev", "rev In.txt", NULL);
                _exit(1);
            }
            dup2(fd1[0], 0);
            dup2(fd2[0], 1);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);
            wait(NULL);
            execlp("rev", "rev", NULL);
            _exit(1);
        }
        dup2(fd2[0], 0);
        close(fd2[0]);
        close(fd2[1]);
        wait(NULL);
        execlp("cmp", "cmp", "-", "In.txt", "-s", NULL);
        _exit(1);
    }
    close(fd2[0]);
    close(fd2[1]);
    wait(NULL);
    printf("FIN\n");
    return 0;
}
// int main()
// {
//     int fd[2];
//     pipe(fd);
//     if (fork() == 0)
//     {
//         dup2(fd[1], 1);
//         close(fd[0]);
//         close(fd[1]);
//         execl("/bin/ls", "ls", NULL);
//         _exit(1);
//     }

//     if (fork() == 0)
//     {
//         dup2(fd[0], 0);
//         close(fd[0]);
//         close(fd[1]);

//         execl("/bin/cat", "cat", NULL);
//         _exit(1);
//     }
//     close(fd[0]);
//     close(fd[1]);
//     while (wait(NULL) > 0)
//     {
//     }
//     return 0;
// }
