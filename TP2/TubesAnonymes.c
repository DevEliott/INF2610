#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    // Processus P3 exécute: "cmp - In.txt -s"
    if (fork() == 0)
    {
        int pipe2[2];
        pipe(pipe2);
        // Processus P2 exécute: "rev"
        if (fork() == 0)
        {
            int pipe1[2];
            pipe(pipe1);
            // Processus P1 exécute: "rev < In.txt"
            if (fork() == 0)
            {
                int fileIn = open("In.txt", O_RDONLY);
                dup2(fileIn, 0);
                close(fileIn);

                dup2(pipe1[1], 1);
                close(pipe1[0]);
                close(pipe1[1]);
                close(pipe2[0]);
                close(pipe2[1]);

                execlp("rev", "rev", NULL);
                _exit(1);
            }
            dup2(pipe1[0], 0);
            dup2(pipe2[1], 1);
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[0]);
            close(pipe2[1]);
            wait(NULL);
            execlp("rev", "rev", NULL);
            _exit(1);
        }
        dup2(pipe2[0], 0);
        close(pipe2[0]);
        close(pipe2[1]);
        wait(NULL);
        execlp("cmp", "cmp", "-", "In.txt", "-s", NULL);
        _exit(1);
    }
    int cmpReturned;
    wait(&cmpReturned);
    if (WIFEXITED(cmpReturned))
        printf("CMP exit code %d\n", WEXITSTATUS(cmpReturned));
    else
        printf("Child did not terminate with exit\n");
    return 0;
}
