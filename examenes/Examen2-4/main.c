#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

int num_cines = 10;

typedef struct taquilla{
    pthread_mutex_t atendiendo;
} taquilla;

typedef struct sala{
    int asientos[50];
    pthread_mutex_t acceso;
    int lleno;
} sala;

typedef struct cine{
    sala salas[3];
    taquilla taquillas[3];
    int lleno;
} cine;

typedef struct caden{
    cine cines[10];
    int lleno;
}caden;

caden cadena;

int checarCadena(){
    for(int i = 0;i < 10; i++){
        if (!cadena.cines[i].lleno){
            return i;
        }
    }
    cadena.lleno = 1;
    return -1;
}

int checarCine(cine cual){
    if(cual.lleno){
        return -1;
    }
    for(int i = 0; i < 3; i++){
        if (!cual.salas[i].lleno){
            return i;
        }
    }
    cual.lleno = 1;
    return -1;
}

int checarSala(sala cual){
    if(cual.lleno){
        return -1;
    }
     for(int i = 0; i < 50; i++){
        if (cual.asientos[i] != 10){
            return i;
        }
    }
    cual.lleno = 1;
    return -1;
}

int comprarBoleto(int cin, int sal, int asient){
    int resultado = 0;
    pthread_mutex_lock(&cadena.cines[cin].salas[sal].acceso);
    if(cadena.cines[cin].salas[sal].asientos[asient] != 10){
        cadena.cines[cin].salas[sal].asientos[asient] = 10;
        printf("Boleto comprado: cine %d, sala %d, asiento %d thread: %d \n", cin, sal,asient, pthread_self());
        resultado = 1;
    }else{
        printf("Compra de boleto fallida: cine %d, sala %d, asiento %d thread: %d\n Probando de nuevo \n", cin, sal,asient, pthread_self());
    }
    pthread_mutex_unlock(&cadena.cines[cin].salas[sal].acceso);
    return resultado;
}


void * formarse(void * p){
    int cin = rand() % 9;
    int atendido = 0;
    int cambio = 0;
    int sal = rand () % 2;
    int asient = rand () % 49;
    int taquill = rand() % 2;
    if(checarCadena() == -1){
        printf("Todos los cines llenos \n");
        pthread_exit(NULL);
    }
    pthread_mutex_lock(&cadena.cines[cin].taquillas[taquill].atendiendo);
    while(!atendido){
        if(cambio){
            pthread_mutex_lock(&cadena.cines[cin].taquillas[taquill].atendiendo);
        }
        cambio = 0;
        if(sal == -1){
            printf("Cine lleno, me voy a otro \n");
            pthread_mutex_unlock(&cadena.cines[cin].taquillas[taquill].atendiendo);
            cadena.cines[cin].lleno = 1;
            cin = checarCadena();
            cambio = 1;
            if ((cin = checarCadena()) == -1){
                printf("Todos los cines llenos \n");
                pthread_exit(NULL);
            }
        }else{
            if(!comprarBoleto(cin,sal,asient)){
                asient = checarSala(cadena.cines[cin].salas[sal]);
                if(asient < 0){
                    cadena.cines[cin].salas[sal].lleno = 1;
                    sal = checarCine(cadena.cines[cin]);
                }
            }else{
                atendido = 1;
            }
        }
    }
    pthread_mutex_unlock(&cadena.cines[cin].taquillas[taquill].atendiendo);
    pthread_exit(NULL);
}


int main()
{
    cadena.lleno = 0;
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 3; j++){
            cadena.cines[i].lleno = 0;
            cadena.cines[i].salas[j].lleno = 0;
        }
    }
    pthread_t clientes[3000];

    for(int i = 0; i < 3000; i++){
        pthread_create(&clientes[i],NULL,formarse,NULL);
    }

    for(int i = 0; i < 3000; i++){
        pthread_join(clientes[i],NULL);
    }
    return 0;
}
