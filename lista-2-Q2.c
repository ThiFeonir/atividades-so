#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *calcula_primo(void *param);


int main(int argc, char *argv[])
{   
    pthread_t tid;

    for(int i = 0; i < argc -1; i++)
        pthread_create(&tid, NULL, calcula_primo, argv[i+1]);

    for(int i = 0; i < argc -1; i++)
        pthread_join(tid, NULL);

    printf("ACABOU!\n");
    
}

void *calcula_primo (void *param)
{   
    int valor = atoi(param);
    if(valor == 1) return 0;
    
    int aux = 0;

    for(int i=2; i <= valor; i++){
        for(int x = 2; x < i; x++){
            if (i % x == 0) aux = 1;
        }   
        if(aux == 0){
            printf("Primos <= %d: %d\n", valor, i);
        }
        aux = 0;    
    }

    pthread_exit(0);
}

