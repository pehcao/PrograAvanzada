#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int HILOS = 10;

int mapa[1001][1001];
int soyThread = 0;
pthread_t threads[10];
int noSig= 0;

void salirUSR1(int inicio){
    noSig = 1;
}

void * cuadrante(void * p){
    soyThread = 1;
    int salida = *((int*)p);
    salida--;
    int entrada = salida - 99;
    int xActual = entrada;
    int yActual = entrada;
    int limite = 0;
    if (mapa[salida][salida]){
        mapa[salida][salida] = 0;
    }
    int encontrado = 0;
    while(!encontrado && !noSig){
        mapa[xActual][yActual] = 2;
        if (limite > 200){
            fprintf("Cuadrante %d - %d no tiene solucion \n", entrada, salida);
            break;
        }
        if(yActual == salida && xActual == salida){
            encontrado = 1;
            break;
        }
        if(yActual == entrada && xActual == entrada){
            if(!mapa[xActual+1][yActual+1]){
                    xActual++;
                    yActual++;
                }else if(!mapa[xActual+1][yActual]){
                    xActual++;
                }else if(!mapa[xActual][yActual+1]){
                    yActual++;
                }else{
                    yActual++;
                    xActual++;
                    if(mapa[entrada+1][entrada+1] = 1){
                        printf("Entrada del cuadrante %d - %d bloqueada, tirando obstaculo \n", entrada, salida);
                        printf("%d, %d\n", xActual, yActual);
                    }

                }
        }else if(xActual == salida){
            if(!mapa[xActual][yActual+1]){
                yActual++;
            }else if(!mapa[xActual-1][yActual+1]){
                yActual++;
                xActual--;
            }else if(!mapa[xActual][yActual-1]){
                xActual--;
            }else if(!mapa[xActual - 1][yActual -1]){
                xActual--;
                yActual--;
            }else{
                yActual--;
            }
        }else if(yActual == salida){
            if(!mapa[xActual+1][yActual]){
                xActual++;
            }
            else if(!mapa[xActual+1][yActual-1]){
                xActual++;
                yActual--;
            }else if(!mapa[xActual][yActual-1]){
                yActual--;
            }else if(!mapa[xActual -1][yActual -1]){
                xActual--;
                yActual--;
            }else{
                xActual--;
            }
        }else if(xActual == entrada){
            if(!mapa[xActual+1][yActual+1]){
                xActual++;
                yActual++;
            }else if(mapa[xActual][yActual+1]){
                yActual++;
            }else if(mapa[xActual+1][yActual]){
                xActual++;
            }
            else if(mapa[xActual][yActual-1]){
                yActual--;
            }else{
                xActual++;
                yActual--;
            }
        }else if(yActual == entrada){
            if(!mapa[xActual+1][yActual+1]){
                xActual++;
                yActual++;
            }else if(mapa[xActual][yActual+1]){
                yActual++;
            }else if(mapa[xActual+1][yActual]){
                xActual++;
            }
            else if(mapa[xActual- 1][yActual]){
                xActual--;
            }else{
                yActual++;
                xActual--;
            }
        }
        else{
            if(!mapa[xActual+1][yActual+1]){
                xActual++;
                yActual++;
            }else if (!mapa[xActual+1][yActual]){
                xActual++;
            }else if (!mapa[xActual][yActual+1]){
                yActual++;
            }else if (!mapa[xActual-1][yActual+1]){
                xActual--;
                yActual++;
            }else if(!mapa[xActual + 1][yActual-1]){
                xActual++;
                yActual--;
            }else if(!mapa[xActual -1][yActual]){
                xActual--;
            }else if(!mapa[xActual][yActual-1]){
                yActual--;
            }else{
                xActual--;
                yActual--;
            }
        }
        limite++;
    }
    for (int i = entrada; i < salida +1; i++){
        for (int j = entrada; j < salida + 1; j++){
            if(mapa[i][j] == 2){
                printf("[%d,%d] \n", i, j);
            }
        }
    }
    printf("%d completado \n", salida);
    pthread_exit();
}


int main()
{
    srand(time(NULL));
    signal(SIGUSR1, salirUSR1);
    mapa[50][50] = 1;
    int * atr = malloc(sizeof(int));
    for (int i = 0;i < rand() % 300; i++){
        for(int j = 0; j < rand() %300; j++){
            mapa[i][j] = 1;
        }
    }
    mapa[1][1] = 0;
    for(int i = 1; i < HILOS + 1; i++){
        *atr = i*100;
        if(*atr <= 1000){
            pthread_create(&threads[i], NULL,cuadrante,(void *) atr);
        }
        sleep(1);
    }
     for(int i = 1; i < HILOS + 1; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}
