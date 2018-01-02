#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fibb(void *param);

int main (int argc, char *argv[])
{   
    pthread_t tid;

    #pragma omp parallel for  
        for(int i = 0; i < argc -1; i++)
        {
            pthread_create(&tid, NULL, fibb, argv[i+1]);
            printf("Thread id %d está executando fibonacci de: %s\n", 
            omp_get_thread_num(), argv[i+1]);
        }
    #pragma omp parallel for
        for(int i = 0; i < argc -1; i++)
            pthread_join(tid, NULL);

    printf("Acabaram as threads!\n");

}

void *fibb(void *param)
{   
    int res, valor = 0;
    valor = res = atoi(param);

    long long fnow = 0, fnext = 1, tempf;
	while(--valor > 0){
		tempf = fnow + fnext;
		fnow = fnext;
		fnext = tempf;
	}

	printf("FIbonacci de %d = %lld  \n", res, fnext);

    pthread_exit(0);
}