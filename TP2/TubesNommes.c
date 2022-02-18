#include <unistd.h>    // pour fork, execl, _exit
#include <stdio.h>     // pour printf
#include <sys/wait.h>  // pour wait
#include <fcntl.h>     // pour open
#include <sys/types.h> // pour mkfifo
#include <sys/stat.h>  // pour mkfifo
#include <stdlib.h>
int main()
{
    // Processus P3 exécute: "cmp - In.txt -s"
    if (fork() == 0)
    {
        // mkfifo("fifo1", 0600);
        mkfifo("fifo2", __S_IREAD | __S_IWRITE);
        // Processus P2 exécute: "rev"
        if (fork() == 0)
        {
            mkfifo("fifo1", __S_IREAD | __S_IWRITE);
            // Processus P1 exécute: "rev < In.txt"
            if (fork() == 0)
            {
                int fileIn = open("In.txt", O_RDONLY);
                dup2(fileIn, 0); // In.txt remplace l'entrée standard
                close(fileIn);

                int fifo1 = open("fifo1", O_WRONLY);
                dup2(fifo1, 1); // Fifo1 remplace sortie standard
                close(fifo1);

                execlp("rev", "rev", NULL); // Rev va lire dans In.txt et écrire dans fifo1
                _exit(1);
            }
            int fifo1 = open("fifo1", O_RDONLY);
            dup2(fifo1, 0); // Fifo1 remplace l'entrée standard
            close(fifo1);

            int fifo2 = open("fifo2", O_WRONLY);
            dup2(fifo2, 1); // Fifo1 remplace la sortie standard
            close(fifo2);

            wait(NULL);
            unlink("fifo1");            // On supprime fifo1
            execlp("rev", "rev", NULL); // Rev va lire dans fifo1 et écrire dans fifo12
            _exit(1);
        }
        int fifo2 = open("fifo2", O_RDONLY);
        dup2(fifo2, 0); // Fifo2 remplace l'entrée standard
        close(fifo2);
        wait(NULL);
        unlink("fifo2");                                 // On supprime fifo2
        execlp("cmp", "cmp", "-", "In.txt", "-s", NULL); // Cmp va lire dans fifo2 et écrire dans la sortie standard
        _exit(1);
    }
    int cmpReturned;
    wait(&cmpReturned); // On attend que le processus P3 termine et on récupère son code de sortie
    if (WIFEXITED(cmpReturned))
        printf("Named pipe: CMP exit code %d\n", WEXITSTATUS(cmpReturned));
    else
        printf("Named pipe: Child did not terminate with exit\n");
    return 0;
}
