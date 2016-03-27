#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

time_t t;
int actual = 0;
int actualE = 100;
int colEvacia = 0;

int atg1 = 0, atg2 = 0, atg3 = 0, atg4 = 0,atg5 = 0, ate1 = 0, ate2 = 0, ate3 = 0;
pthread_mutex_t mg1, mg2, mg3, mg4, mg5, me1, me2, me3, turno, turnoE, colE;

void * formarseEmpresarial(void *p){
int atendido = 0;
    int numero = p;
    printf("Cliente %d formado en empresarial\n", p);
    pthread_mutex_lock(&colE);
    colEvacia ++;
    pthread_mutex_unlock(&colE);
    while(actualE != numero){

    }
    while(!atendido){
        if(pthread_mutex_trylock(&me1)== 0){
            pthread_mutex_lock(&turnoE);
            actualE++;
            pthread_mutex_unlock(&turnoE);
            printf("Cajero empresarial 1 atendiendo cliente %d \n", p);
            sleep((rand() % 3)+ 2);
            ate1++;
            atendido = 1;
            if(ate1 == 5){
                printf("Cajero empresarial 1 descansando \n");
                sleep(3);
                ate1 = 0;
            }
            pthread_mutex_unlock(&me1);
        }
        else if(pthread_mutex_trylock(&me2)== 0){
            pthread_mutex_lock(&turnoE);
            actualE++;
            pthread_mutex_unlock(&turnoE);
            printf("Cajero empresarial 2 atendiendo cliente %d \n", p);
            sleep((rand() % 3)+ 2);
            atendido = 1;
            ate2++;
            if(ate2 == 5){
                printf("Cajero empresarial 2 descansando \n");
                sleep(3);
                ate2 = 0;
            }
            pthread_mutex_unlock(&me2);
        }
        else if(pthread_mutex_trylock(&me3)== 0){
            pthread_mutex_lock(&turnoE);
            actualE++;
            pthread_mutex_unlock(&turnoE);
            printf("Cajero empresarial 3 atendiendo cliente %d \n", p);
            sleep((rand() % 3)+ 2);
            atendido = 1;
            ate3++;
            if(ate3 == 5){
                printf("Cajero empresarial 3 descansando \n");
                sleep(3);
                ate3 = 0;
            }
            pthread_mutex_unlock(&me3);
        }
    }
    pthread_mutex_lock(&colE);
    colEvacia--;
    pthread_mutex_unlock(&colE);
    pthread_exit(NULL);
}


void * formarseGeneral(void * p){
    int atendido = 0;
    int numero = p;
    printf("Cliente %d formado \n", p);
    while(actual != numero){

    }
    while(!atendido){
        if(pthread_mutex_trylock(&mg1)== 0){
            pthread_mutex_lock(&turno);
            actual++;
            pthread_mutex_unlock(&turno);
            printf("Cajero general 1 atendiendo cliente %d \n", p);
            sleep((rand() % 3)+ 2);
            atg1++;
            atendido = 1;
            if(atg1 == 5){
                printf("Cajero general 1 descansando \n");
                sleep(3);
                atg1 = 0;
            }
            pthread_mutex_unlock(&mg1);
        }
        else if(pthread_mutex_trylock(&mg2)== 0){
            pthread_mutex_lock(&turno);
            actual++;
            pthread_mutex_unlock(&turno);
            printf("Cajero general 2 atendiendo cliente %d \n", p);
            sleep((rand() % 3)+ 2);
            atendido = 1;
            atg2++;
            if(atg2 == 5){
                printf("Cajero general 2 descansando \n");
                sleep(3);
                atg2 = 0;
            }
            pthread_mutex_unlock(&mg2);
        }
        else if(pthread_mutex_trylock(&mg3)== 0){
            pthread_mutex_lock(&turno);
            actual++;
            pthread_mutex_unlock(&turno);
            printf("Cajero general 3 atendiendo cliente %d \n", p);
            sleep((rand() % 3)+ 2);
            atendido = 1;
            atg3++;
            if(atg3 == 5){
                printf("Cajero general 3 descansando \n");
                sleep(3);
                atg3 = 0;
            }
            pthread_mutex_unlock(&mg3);
        }
        else if(pthread_mutex_trylock(&mg4)== 0){
            pthread_mutex_lock(&turno);
            actual++;
            pthread_mutex_unlock(&turno);
            printf("Cajero general 4 atendiendo cliente %d \n", p);
            sleep((rand() % 3)+ 2);
            atendido = 1;
            atg4++;
            if(atg4 == 5){
                printf("Cajero general 4 descansando \n");
                sleep(3);
                atg4 = 0;
            }
            pthread_mutex_unlock(&mg4);
        }
        else if(pthread_mutex_trylock(&mg5)== 0){
            pthread_mutex_lock(&turno);
            actual++;
            pthread_mutex_unlock(&turno);
            printf("Cajero general 5 atendiendo cliente %d \n", p);
            sleep((rand() % 3)+ 2);
            atendido = 1;
            atg5++;
            if(atg5 == 5){
                printf("Cajero general 5 descansando \n");
                sleep(3);
                atg5 = 0;
            }
            pthread_mutex_unlock(&mg5);
        }
        else if(!colEvacia){
            if(pthread_mutex_trylock(&me1)== 0){
                pthread_mutex_lock(&turno);
                actual++;
                pthread_mutex_unlock(&turno);
                printf("Cajero empresarial 1 atendiendo cliente %d \n", p);
                sleep((rand() % 3)+ 2);
                ate1++;
                atendido = 1;
                if(ate1 == 5){
                    printf("Cajero empresarial 1 descansando \n");
                    sleep(3);
                    ate1 = 0;
                }
                pthread_mutex_unlock(&me1);
            }
            else if(pthread_mutex_trylock(&me2)== 0){
                pthread_mutex_lock(&turno);
                actual++;
                pthread_mutex_unlock(&turno);
                printf("Cajero empresarial 2 atendiendo cliente %d \n", p);
                sleep((rand() % 3)+ 2);
                atendido = 1;
                ate2++;
                if(ate2 == 5){
                    printf("Cajero empresarial 2 descansando \n");
                    sleep(3);
                    ate2 = 0;
                }
                pthread_mutex_unlock(&me2);
            }
            else if(pthread_mutex_trylock(&me3)== 0){
                pthread_mutex_lock(&turno);
                actual++;
                pthread_mutex_unlock(&turno);
                printf("Cajero empresarial 3 atendiendo cliente %d \n", p);
                sleep((rand() % 3)+ 2);
                atendido = 1;
                ate3++;
                if(ate3 == 5){
                    printf("Cajero empresarial 3 descansando \n");
                    sleep(3);
                    ate3 = 0;
                }
                pthread_mutex_unlock(&me3);
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    srand((unsigned) time(&t));
    pthread_t clientes[150];

    for(int i = 0; i < 150; i++){
        if (i < 100){
            pthread_create(&clientes[i], NULL,formarseGeneral, i);
        }else{
            pthread_create(&clientes[i], NULL,formarseEmpresarial, i);
        }
    }

    for(int i = 0;i < 150; i++){
        pthread_join(clientes[i], NULL);
    }

    return 0;
}
