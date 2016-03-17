#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct cajero{
    int atendidos;
    int id;
    pthread_mutex_t atendiendo;
}cajero;

time_t t;

int generales = 5;
int empresariales = 3;



void * formarseEmpresarial(void *p){
    int * cajeros = (cajeros *)malloc(sizeof(cajero)*3);
    int atendido = 0;
    while (!atendido){
        for(int i = 0; i < 3 ;i ++){
            if(!pthread_mutex_trylock(&(((cajero)*(cajeros + i))->atendiendo))){
                printf("Cajero empresarial %d atendiendo cliente %d", *(cajeros+i)->id, pthread_self());
                sleep((rand() % 3)+2);
                *(cajeros+i)->atendidos++;
                pthread_mutex_unlock(&(((cajero)*(cajeros + i))->atendiendo));
            }
        }
    }
    pthread_exit(NULL);

}

void checarRecesosG(cajero * gens){
    for (int i = 0; i < 5; i++){
        if(*(cajero+i)->atendidos > 4){
            pthread_mutex_lock(&(((cajero)*(cajeros + i))->atendiendo));
            sleep(3);
            pthread_mutex_unlock(&(((cajero)*(cajeros + i))->atendiendo));
        }
    }
}

void checarRecesosE(cajero * emps){
    for (int i = 0; i < 3; i++){
        if(*(cajero+i)->atendidos > 4){
            pthread_mutex_lock(&(((cajero)*(cajeros + i))->atendiendo));
            sleep(3);
            pthread_mutex_unlock(&(((cajero)*(cajeros + i))->atendiendo));
        }
    }
}

void * formarseGeneral(void * p){
    int * cajeros = (cajeros *) malloc(sizeof(cajero)*5);
    int atendido = 0;
    while (!atendido){
        for(int i = 0; i < 5 ;i ++){
            if(!pthread_mutex_trylock(&(((cajero)*(cajeros + i))->atendiendo))){
                printf("Cajero general %d atendiendo cliente %d", *(cajeros+i)->id, pthread_self());
                sleep((rand() % 3)+2);
                *(cajeros+i)->atendidos++;
                pthread_mutex_unlock(&(((cajero)*(cajeros + i))->atendiendo));
            }
        }
    }
    pthread_exit(NULL);
}


int main()
{
    srand((unsigned) time_t(&t));
    cajero genes[5];
    cajero empres[3];

    cajero general;
    general.id = 1;
    general.atendidos = 0;
    cajero general1;
    cajero general2;
    cajero general3;
    cajero general4;

    general1.id = 2;
    general1.atendidos = 0;
    general2.id = 3;
    general2.atendidos = 0;
    general3.id = 4;
    general3.atendidos = 0;
    general4.id = 5;
    general4.atendidos = 0;

    genes[0] = general;
    genes[1] = general1;
    genes[2] = general2;
    genes[3] = general3;
    genes[4] = general4;

    cajero empresarial;
    cajero empresarial1;
    cajero empresarial2;

    empresarial.id = 1;
    empresarial1.id = 2;
    empresarial2.id = 3;

    empres[0] = empresarial;
    empres[1] = empresarial1;
    empres[2] = empresarial2;



    pthread_mutex_t gen;
    general.atendiendo = gen;
    pthread_mutex_t gen1;
    general1.atendiendo = gen1;
    pthread_mutex_t gen2;
    general2.atendiendo =gen2;
    pthread_mutex_t gen3;
    general3.atendiendo = gen3;
    pthread_mutex_t gen4;
    general4.atendiendo = gen4;

    pthread_mutex_t emp;
    empresarial.atendiendo = emp;
    pthread_mutex_t emp1;
    empresarial1.atendiendo = emp1;
    pthread_mutex_t emp2;
    empresarial2.atendiendo = emp2;

    pthread_t clientes[150];

    for(int i = 0; i < 150; i++){
        if (i < 50){
            pthread_create(&clientes[i], NULL,formarseEmpresarial, &empres);
        }else{
            pthread_create(&clientes[i],NULL,formarseGeneral, &genes);
        }
        checarRecesosE(empres);
        checarRecesosG(genes);
    }

    for(int i = 0;i < 150; i++){
        pthread_join(clientes[i], NULL);
    }

    return 0;

}
