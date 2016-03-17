#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int tenedores=3;
int cuchillos=3;
int sillas = 4;

typedef struct params{
    pthread_mutex_t mutexTenedores;
    pthread_mutex_t mutexCuchillos;
    pthread_mutex_t mutexSillas;
}param;


void * comer(void * p){
    param * pa = (param *)p;
    int termine = 0;
    while(!termine){
        pthread_mutex_lock(&pa->mutexTenedores);
        if (tenedores > 0){
            pthread_mutex_lock(&pa->mutexCuchillos);
            printf("Hay %d cuchillos \n", cuchillos);
            if (cuchillos > 0){
                tenedores--;
                cuchillos--;
                printf("Thread numero %d comiendo \n", pthread_self());
                sleep(4);
                termine = 1;
            }
            pthread_mutex_unlock(&pa->mutexCuchillos);
        }
        pthread_mutex_unlock(&pa->mutexTenedores);
    }
    tenedores++;
    cuchillos++;
    printf("Thread numero %d termino de comer \n", pthread_self());
}

void * sentarse(void * p){
    param * pa = (param *)p;
    int satisfecho = 0;
    while(!satisfecho){fa
        pthread_mutex_lock(&pa->mutexSillas);
        if (sillas > 0){
            sillas--;
            printf("Thread numero %d sentandose quedan %d sillas\n", pthread_self(), sillas);
            comer(p);
            satisfecho = 1;
        }
        pthread_mutex_unlock(&pa->mutexSillas);
    }
    sillas++;
    printf("Thread numero %d ya se va quedan %d sillas\n", pthread_self(), sillas);
    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_t mut;
    pthread_mutex_t mut1;
    pthread_mutex_t mut2;

    pthread_t thread[100];

    param p;
    p.mutexTenedores = mut;
    p.mutexCuchillos= mut1;
    p.mutexSillas = mut2;

    for(int i = 0; i < 100; i++){
        pthread_create(&thread[i], NULL,sentarse, &p);
        sleep(1);
    }

    for(int i = 0;i < 100; i++){
    pthread_join(thread[i], NULL);
    }
    return 0;
}
