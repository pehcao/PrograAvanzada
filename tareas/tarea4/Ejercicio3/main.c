#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int secciones[5][1];
int pMaximo = 500;
pthread_cond_t conds[5] = PTHREAD_COND_INITIALIZER;
pthread_mutex_t muts[5];

void * robot_entra(void * p){
    int peso = (rand() % 200) + 100;
    int entre = 0;
    for(int i = 0; i < 5; i++){
        entre = 0;
        while(!entre){
            pthread_mutex_lock(&muts[i]);
            if((secciones[i][0] + peso) > pMaximo){
                pthread_cond_wait(&conds[i],&muts[i]);
                pthread_mutex_unlock(&muts[i]);
            }else{
                secciones[i][0]+= peso;
                pthread_mutex_unlock(&muts[i]);
                printf("Robot peso %d entro a seccion %d, peso actual %d \n", peso, i, secciones[i][0]);
                entre = 1;
                sleep((rand() % 5) + 2);
                pthread_mutex_lock(&muts[i]);
                secciones[i][0]-= peso;
                printf("Robot peso %d salio de seccion %d, peso actual %d \n", peso, i, secciones[i][0]);
                pthread_mutex_unlock(&muts[i]);
                pthread_cond_broadcast(&conds[i]);
            }
        }
    }
    printf("Robot peso %d termino y ya se va \n", peso);
    pthread_exit(NULL);
}

int main()
{
    printf("Peso maximo: %d\n",pMaximo);
    srand(time(NULL));
    pthread_t robots[50];
    for(int i = 0; i < 5; i++){
        secciones[i][0] = 0;
    }
    for(int i = 0; i < 10; i++){
        pthread_create(&robots[i],NULL,robot_entra,NULL);
        sleep(rand() % 2);
    }

    for(int i = 0; i < 3; i++){
        pthread_join(robots[i], NULL);
    }
    return 0;
}
