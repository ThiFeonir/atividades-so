#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int primos[100];

void *calcula_primo(void *param);

int main(int argc, char *argv[])
{   
    pthread_t tid_primo;

    for(int i = 0; i < argc -1; i++)
        pthread_create(&tid_primo, NULL, calcula_primo, argv[i+1]);

    for(int i = 0; i < argc -1; i++)
        pthread_join(tid_primo, NULL);

    printf("ACABOU!\n");

    for(int i = 0; i < 50; i++){
        if(primos[i] != NULL)
            printf("Valor em primos[%d] = %d\n", i, primos[i]);
    }
}

void *calcula_primo(void *param)
{   
    int i = 0; int aux = 0; int valor = atoi(param);

    while(primos[i] != NULL && primos[i] <= valor)
    {
        printf("Primo <= %d: %d\n", valor, primos[i]);
        printf("Estou no while\n");
        i++;
    }
    
    if (i <= valor)
    {
        for(int k=2; k <= valor; k++){
            for(int x = 2; x < k; x++){
                if (k % x == 0) aux = 1;
            }   
            if(aux == 0){
                printf("Primos <= %d: %d\n", valor, k);
                primos[i++] = k;
            }
            aux = 0;    
        }
    }
}