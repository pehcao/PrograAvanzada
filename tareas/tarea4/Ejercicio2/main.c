#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

enum { M, H , V} dentro;
pthread_cond_t condM = PTHREAD_COND_INITIALIZER;
pthread_cond_t condH = PTHREAD_COND_INITIALIZER;

pthread_mutex_t sumaH;
pthread_mutex_t sumaM;
pthread_mutex_t Mbano;

int hombres = 0;
int mujeres = 0;
int bano = 0;

void mujer_sale(){
    sleep((rand() % 5) + 5);
    printf("Mujer sale \n");
    pthread_mutex_lock(&Mbano);
    bano--;
    if(bano == 0){
        dentro = V;
        printf("Sanitario vacio \n");
        if(hombres > 0){
            printf("Sanitario ocupado por Hombres \n");
        }
        pthread_cond_broadcast(&condH);
    }
    pthread_mutex_unlock(&Mbano);
    pthread_exit(NULL);
}

void hombre_sale(){
    sleep((rand() % 5) + 2);
    printf("Hombre sale \n");
    pthread_mutex_lock(&Mbano);
    bano--;
    if(bano == 0){
        dentro = V;
        printf("Sanitario vacio \n");
        if(mujeres > 0){
            printf("Sanitario ocupado por Mujeres \n");
        }
        pthread_cond_broadcast(&condM);
    }
    pthread_mutex_unlock(&Mbano);
    pthread_exit(NULL);
}

void * mujer_quiere_entrar(void * p)
{
    pthread_mutex_lock(&sumaM);
    mujeres++;
    printf("Mujer quiere entrar (En espera %d) \n", mujeres);
    pthread_mutex_unlock(&sumaM);

    pthread_mutex_lock(&Mbano);
    if(dentro == V){
        dentro = M;
        printf("Sanitario ocupado por Mujeres \n");
    }else if(dentro == H){
        pthread_cond_wait(&condM, &Mbano);
        dentro = M;
    }
    bano++;
    pthread_mutex_unlock(&Mbano);
    pthread_mutex_lock(&sumaM);
    mujeres--;
    printf("Mujer entra (En espera %d) \n", mujeres);
    pthread_mutex_unlock(&sumaM);
    mujer_sale();
}

void * hombre_quiere_entrar(void * p)
{
    pthread_mutex_lock(&sumaH);
    hombres++;
    printf("Hombre quiere entrar (En espera %d) \n", hombres);
    pthread_mutex_unlock(&sumaH);

    pthread_mutex_lock(&Mbano);
    if(dentro == V){
        dentro = H;
        printf("Sanitario ocupado por Hombres \n");
    }else if(dentro == M){
        pthread_cond_wait(&condH, &Mbano);
        dentro = H;
    }
    bano++;
    pthread_mutex_unlock(&Mbano);
    pthread_mutex_lock(&sumaH);
    hombres--;
    printf("Hombre entra (En espera %d) \n", hombres);
    pthread_mutex_unlock(&sumaH);
    hombre_sale();
}

int main(){
    srand(time(NULL));
    pthread_t alumnos[50];
    int val;
    for(int i = 0; i < 50; i++){
        val = rand() % 2;
        if(i == 0){
            if(val){
                dentro = H;
                pthread_create(&alumnos[i],NULL,hombre_quiere_entrar,NULL);
            }else{
                dentro = M;
                pthread_create(&alumnos[i],NULL,mujer_quiere_entrar,NULL);
            }
        }else{
            if(val){
                pthread_create(&alumnos[i],NULL,hombre_quiere_entrar,NULL);
            }else{
                pthread_create(&alumnos[i],NULL,mujer_quiere_entrar,NULL);
            }
        }
         sleep(rand() % 5);
    }

    for(int i = 0; i < 50; i++){
        pthread_join(alumnos[i], NULL);
    }
}
