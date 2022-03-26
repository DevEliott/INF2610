/**
 * @file GuerreDesLettres.c
 * @author Eliott Schuhmacher-Wantz (2081542) & Ivan Ivanov (2087256)
 * @date 2022-03-25
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

char *tampon;
int *nb_lettres_produites;
int *nb_lettres_consommées;
int taille_tampon;
int ip = 0;
int ic = 0;

sem_t libre;  // semaphore pour les jetons de production dans le tampon et la mise en attente du producteur lorsque le tampon est plein
sem_t occupe; // pour les jetons de consommation du tampon et la mise en attente du consommateur lorsque le tampon est vide
sem_t mutex;  // mutex permet d’assurer un accès exclusif aux variables partagées ic, ip et le tampon

int flag_de_fin = 0;

void *producteur(void *pid)
{
    int id = *(int *)pid;
    while (1)
    {
        sem_wait(&libre);
        sem_wait(&mutex);
        tampon[ip] = 'A' + rand() % 26;
        ip = (ip + 1) % taille_tampon;
        sem_post(&mutex);
        sem_post(&occupe);
        nb_lettres_produites[id]++;
        if (flag_de_fin)
        {
            printf("Producteur %d a produit %d lettres\n", id, nb_lettres_produites[id]);
            pthread_exit(NULL);
        }
    }
}

void *consommateur(void *cid)
{
    int id = *(int *)cid;
    while (1)
    {
        sem_wait(&occupe);
        sem_wait(&mutex);
        char lettre = tampon[ic];
        ic = (ic + 1) % taille_tampon;
        sem_post(&mutex);
        sem_post(&libre);
        if (lettre == '0')
        {
            printf("Consommateur %d a consommé %d lettres\n", id, nb_lettres_consommées[id]);
            pthread_exit(NULL);
        }
        else
        {
            nb_lettres_consommées[id]++;
        }
    }
}

void handle_alarm(int signal)
{
    flag_de_fin = 1;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <taille_tampon> <nb_producteurs> <nb_consommateurs>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    int nb_producteurs = atoi(argv[1]);
    int nb_consommateurs = atoi(argv[2]);
    taille_tampon = atoi(argv[3]);

    nb_lettres_produites = malloc(nb_producteurs * sizeof(int));
    nb_lettres_consommées = malloc(nb_consommateurs * sizeof(int));
    tampon = malloc(taille_tampon * sizeof(char));

    sem_init(&libre, 0, taille_tampon);
    sem_init(&occupe, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t *ids_producteurs = malloc(nb_producteurs * sizeof(pthread_t));
    pthread_t *ids_consommateurs = malloc(nb_consommateurs * sizeof(pthread_t));

    for (int i = 0; i < nb_producteurs; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&ids_producteurs[i], NULL, producteur, arg);
    }

    for (int i = 0; i < nb_consommateurs; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&ids_consommateurs[i], NULL, consommateur, arg);
    }

    signal(SIGALRM, handle_alarm);
    alarm(1);

    int nb_productions_total = 0;
    for (int i = 0; i < nb_producteurs; i++)
    {
        pthread_join(ids_producteurs[i], NULL);
        nb_productions_total += nb_lettres_produites[i];
    }

    for (int i = 0; i < nb_consommateurs; i++)
    {
        sem_wait(&libre);
        sem_wait(&mutex);
        tampon[ip] = '0';
        ip = (ip + 1) % taille_tampon;
        sem_post(&mutex);
        sem_post(&occupe);
    }

    int nb_consommations_total = 0;
    for (int i = 0; i < nb_consommateurs; i++)
    {
        pthread_join(ids_consommateurs[i], NULL);
        nb_consommations_total += nb_lettres_consommées[i];
    }

    printf("Nombre total de productions   = %d\n", nb_productions_total);
    printf("Nombre total de consommations = %d\n", nb_consommations_total);

    free(tampon);
    free(ids_producteurs);
    free(ids_consommateurs);
    free(nb_lettres_produites);
    free(nb_lettres_consommées);

    sem_destroy(&libre);
    sem_destroy(&occupe);
    sem_destroy(&mutex);
    return 0;
}