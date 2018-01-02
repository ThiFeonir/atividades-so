#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int medio, maximo, minimo;

void *calcula_media(void *param);
void *calcula_minimo(void *param);
void *calcula_maximo(void *param);

int main(int argc, char *argv[])
{
    pthread_t tid_maximo;
    pthread_t tid_medio;
    pthread_t tid_minimo;

    int valores [argc-1];

    for (int i = 1; i <argc; i++){
         valores[i-1] = atoi(argv[i]);
    }
    pthread_create(&tid_maximo, NULL, calcula_maximo,valores);
    pthread_create(&tid_medio, NULL, calcula_media,valores);
    pthread_create(&tid_minimo, NULL, calcula_minimo, valores);

    pthread_join(tid_maximo, NULL);
    pthread_join(tid_medio, NULL);
    pthread_join(tid_minimo, NULL);

    printf("maximo = %d\n",maximo);
    printf("medio = %d\n", medio);
    printf("minimo = %d\n", minimo);
}

void *calcula_maximo(void *param)
{
    int * vetor = (int *) param;
    int tam = sizeof(vetor)/sizeof(vetor[0]);
    maximo = 0;

    for (int i = 0; i <= tam; i++){
        if (maximo < vetor[i])
            maximo = vetor[i];
    }
}


void *calcula_media(void *param)
{
    int * vetor = (int *) param;
    int tam = sizeof(vetor)/sizeof(vetor[0]);

    medio = 0;

    for (int i = 0; i <= tam; i++){
        medio += vetor[i];
    }

    medio /= tam;
}


void *calcula_minimo(void *param)
{
    int * vetor = (int *) param;
    int tam = sizeof(vetor)/sizeof(vetor[0]);
    minimo = vetor[0];

    for (int i = 1; i <= tam; i++){
        if (minimo > vetor[i])
            minimo = vetor[i];
    }
}
