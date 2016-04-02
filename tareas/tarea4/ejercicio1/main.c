#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

sem_t sillas;
sem_t comer;
sem_t servido;
int todos = 0;
pthread_mutex_t sirviendo;
int serv = 0;
pthread_mutex_t sumar;


void * Enano(void * p){
    int n = p;
    int x = 0;
    while(x++ < 10){
        sleep(rand() % 5);
        sem_wait(&sillas);
        printf("Enano %d sentado \n", n);
        sem_wait(&comer);
        pthread_mutex_lock(&sirviendo);
        serv = n;
        sem_wait(&servido);
        pthread_mutex_unlock(&sirviendo);
        printf("Enano %d comiendo \n", n);
        sem_post(&comer);
        sleep((rand() % 5)+3);
        sem_post(&sillas);
        printf("Enano %d termino de comer \n", n);
    }
    pthread_mutex_lock(&sumar);
        todos++;
        pthread_mutex_unlock(&sumar);
    pthread_exit(NULL);
}

int main(){
    srand(time(NULL));
    pthread_t enanos[7];
    sem_init(&sillas,0,4);
    sem_init(&comer,0,4);
    sem_init(&servido,0,0);
    for (int i = 0; i < 7; i++){
        pthread_create(&enanos[i],NULL,Enano, i);
    }
    int pidiendo;
    int lugares;
    while(todos < 7){
        sem_getvalue(&comer,&pidiendo);
        sem_getvalue(&sillas,&lugares);
        if(pidiendo < 4){
            printf("Blancanieves sirviendo a enano %d \n", serv);
            sem_post(&servido);
            sleep(1);
        }else if(lugares < 4){
            printf("Blancanieves paseando \n");
            sleep((rand() % 5)+3);
             sem_getvalue(&comer,&pidiendo);
            sem_getvalue(&sillas,&lugares);
            printf("Blancanieves regreso \n sillas: %d pendientes: %d \n", lugares, (4- pidiendo));
        }
    }
    for(int i = 0; i < 7; i++){
        pthread_join(enanos[i],NULL);
    }
}
