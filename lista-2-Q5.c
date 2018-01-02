/*Alguns algoritmos de ordenação não funcionam perfeitamente: heap e insertion*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct thread_data{
    int *array;
    int inicio;
    int fim;
};

struct thread_data thread_data;

void *bubble_sort (void *thread_param);
void *insertion_sort(void *thread_param);
void *selection_sort (void *thread_param);
void *heapsort (void *thread_param);
void downheap (int *a, int n, int i);
void quicksort(int *A, int len);
int max (int *a, int n, int i, int j, int k);

int main(int argc, void *argv[])
{
    int a[atoi(argv[1])];
    int n = sizeof a / sizeof a[0];
    int i;
    pthread_t tid_heap;
    pthread_t tid_bubble;
    pthread_t tid_insertion;
    pthread_t tid_selection;
    pthread_attr_t attr;

    thread_data.array = a;
    thread_data.inicio = 0;

    for(i = 0; i < n; i++){
        int r = rand() % 20;
        a[i] = r;
    }

    pthread_attr_init(&attr);
    
    for (i = 0; i < n; i++)
        printf("%d%s", a[i], i == n - 1 ? "\n" : " ");

    printf("Vai criar a thread\n");

    for(int x = 10; x <= n; x += 10)
    {
        int thread_atual = rand() % 4;
        //int thread_atual = 3;    

        printf("n = %d , x = %d e thread_atual = %d\n", n, x, thread_atual);

        switch (thread_atual)
        {
            case 0:
                thread_data.fim = x;

                pthread_create(&tid_bubble, NULL, bubble_sort, (void *) &thread_data);

                pthread_join(tid_bubble, NULL);

                for (i = 0; i < n; i++)
                printf("%d%s", a[i], i == n - 1 ? "\n" : " ");

                thread_data.inicio = thread_data.fim;
                printf("inicio = %d , fim = %d\n", thread_data.inicio, thread_data.fim);
                break;

            case 1:
                thread_data.fim = x;

                pthread_create(&tid_insertion, NULL, insertion_sort, (void *) &thread_data);

                pthread_join(tid_insertion, NULL);

                for (i = 0; i < n; i++)
                printf("%d%s", a[i], i == n - 1 ? "\n" : " ");

                thread_data.inicio = thread_data.fim;

                printf("inicio = %d , fim = %d\n", thread_data.inicio, thread_data.fim);
                break;

            case 2:
                thread_data.fim = x;

                pthread_create(&tid_heap, NULL, heapsort, (void *) &thread_data);

                pthread_join(tid_heap, NULL);

                for (i = 0; i < n; i++)
                printf("%d%s", a[i], i == n - 1 ? "\n" : " ");

                thread_data.inicio = thread_data.fim;

                printf("inicio = %d , fim = %d\n", thread_data.inicio, thread_data.fim);
                break;  

            case 3:
                thread_data.fim = x;

                pthread_create(&tid_selection, NULL, selection_sort, (void *) &thread_data);

                pthread_join(tid_selection, NULL);

                for (i = 0; i < n; i++)
                printf("%d%s", a[i], i == n - 1 ? "\n" : " ");

                thread_data.inicio = thread_data.fim;

                printf("inicio = %d , fim = %d\n", thread_data.inicio, thread_data.fim);
                break; 
        }
    }

    printf("Thread terminada...\n");
    

    quicksort(a, n);

    for (i = 0; i < n; i++)
                printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    return 0;
}

void *bubble_sort (void *thread_param) {
    int i, t, s = 1, *a, n;
    struct thread_data *my_data;

    my_data = (struct thread_data *) thread_param;
    a = my_data->array;
    n = my_data->fim;

    while (s) {
        s = 0;
        for (i = my_data->inicio +1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
    }

    pthread_exit(0);
}

void *insertion_sort(void *thread_param) {
    
    int *a, n;
    struct thread_data *my_data;

    my_data = (struct thread_data *) thread_param;
    a = my_data->array;
    n = my_data->fim;

	for(int i = (int *) my_data->inicio + 1; i < n; ++i) {
		int tmp = a[i];
		int j = i;
		while(j > 0 && tmp < a[j - 1]) {
			a[j] = a[j - 1];
			--j;
		}
		a[j] = tmp;
	}
    pthread_exit(0);
}

void *selection_sort (void *thread_param) {

    int *a, n;
    struct thread_data *my_data;

    my_data = (struct thread_data *) thread_param;
    a = my_data->array;
    n = my_data->fim;

    int i, j, m, t;
    for (i = my_data->inicio; i < n; i++) {
        for (j = i, m = i; j < n; j++) {
            if (a[j] < a[m]) {
                m = j;
            }
        }
        t = a[i];
        a[i] = a[m];
        a[m] = t;
    }
}

int max (int *a, int n, int i, int j, int k) {
    int m = i;
    if (j < n && a[j] > a[m]) {
        m = j;
    }
    if (k < n && a[k] > a[m]) {
        m = k;
    }
    return m;
}
 
void downheap (int *a, int n, int i) {
    while (1) {
        int j = max(a, n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
        i = j;
    }
}
 
void *heapsort (void *thread_param) {

    int *a, n;
    struct thread_data *my_data;

    my_data = (struct thread_data *) thread_param;
    a = my_data->array;
    n = my_data->fim;

    int i;
    for (i = (n - 2) / 2; i >= my_data->inicio; i--) {
        downheap(a, n, i);
    }
    for (i = my_data->inicio ; i < n; i++) {
        int t = a[n - i - 1];
        a[n - i - 1] = a[0];
        a[0] = t;
        downheap(a, n - i - 1, 0);
    }
}

void quicksort(int *A, int len) {
  if (len < 2) return;
 
  int pivot = A[len / 2];
 
  int i, j;
  for (i = 0, j = len - 1; ; i++, j--) {
    while (A[i] < pivot) i++;
    while (A[j] > pivot) j--;
 
    if (i >= j) break;
 
    int temp = A[i];
    A[i]     = A[j];
    A[j]     = temp;
  }
 
  quicksort(A, i);
  quicksort(A + i, len - i);
}
