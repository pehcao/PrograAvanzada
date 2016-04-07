#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

pthread_mutex_t mutTabaco, mutPapel, mutFosf;
pthread_cond_t tabaco = PTHREAD_COND_INITIALIZER;
pthread_cond_t papel = PTHREAD_COND_INITIALIZER;
pthread_cond_t fosforos = PTHREAD_COND_INITIALIZER;

int tabProducido = 0;
int papProducido = 0;
int fosfProducido = 0;

int tabEnMesa;
int papEnMesa;
int fosfEnMesa;


void * agente(void *p){
    while(1){
        if(tabProducido && !tabEnMesa){
            tabProducido= 0;
            tabEnMesa = 1;
            printf("Ya hay tabaco \n");
        }
        if(papProducido && !papEnMesa){
            papProducido= 0;
            papEnMesa = 1;
            printf("Ya hay papel \n");
        }
        if(fosfProducido && !fosfEnMesa){
            fosfProducido = 0;
            fosfEnMesa = 1;
            printf("Ya hay fosforos \n");
        }
        printf("Agente haciendo otras actividades \n");
        sleep(5);
    }
    pthread_exit(NULL);
}


void * fumarTab(void * p){
    int fumando = 0;
    time_t espera = 0;
    tabEnMesa = 0;
    tabProducido = 0;
    int printed= 1;
    while(1){
            sleep(1);
        if(time(NULL) < espera){
            if (tabProducido == 0){
                tabProducido = 1;
                printf("Produje tabaco \n");
            }
        }else{
            if(!printed){
                printf("Productor de tabaco ya puede fumar de nuevo \n");
                printed = 1;
            }
            if (tabProducido == 0){
                tabProducido = 1;
                printf("Produje tabaco \n");
            }
            pthread_mutex_lock(&mutTabaco);
             if(tabEnMesa){
                printf("Hay tabaco \n");
                pthread_mutex_lock(&mutPapel);
                sleep(1);
                if(papEnMesa){
                    printf("Hay papel \n");
                    pthread_mutex_lock(&mutFosf);
                    sleep(1);
                    if(fosfEnMesa){
                        printf("Hay fosforos \n");
                        fumando++;
                        printf("Productor de tabaco fumando \n");
                    }else{
                    pthread_mutex_unlock((&mutFosf));
                    pthread_mutex_unlock(&mutPapel);
                    pthread_mutex_unlock(&mutTabaco);
                    }
                }else{
                    pthread_mutex_unlock(&mutPapel);
                    pthread_mutex_unlock(&mutTabaco);
                }
            }else{
                pthread_mutex_unlock(&mutTabaco);
            }
            if (fumando){
                    pthread_mutex_unlock(&mutFosf);
                    pthread_mutex_unlock(&mutTabaco);
                    pthread_mutex_unlock(&mutPapel);
                    tabEnMesa--;
                    papEnMesa--;
                    fosfEnMesa--;
                    sleep(2);
                    printed = 0;
                    printf("Productor de tabaco regreso de fumar \n");
                    espera = time(NULL) + 4;
                }
        }
    }
    pthread_exit(NULL);
}

void *fumarPap(void *p){
    int fumando = 0;
    papEnMesa = 0;
    papProducido = 0;
    time_t espera = 0;
    int printed= 1;
    while(1){
            sleep(1);
        if(time(NULL) < espera){
            if (papProducido == 0){
                papProducido = 1;
                printf("Produje papel \n");

            }
        }else{
            if(!printed){
                printf("Productor de papel ya puede fumar de nuevo \n");
                printed = 1;
            }
            if (papProducido == 0){
                papProducido = 1;
                printf("Produje papel \n");
                }
            pthread_mutex_lock(&mutTabaco);
             if(tabEnMesa){
                printf("Hay tabaco \n");
                pthread_mutex_lock(&mutPapel);
                sleep(1);
                if(papEnMesa){
                        printf("Hay papel \n");
                    pthread_mutex_lock(&mutFosf);
                    sleep(1);
                    if(fosfEnMesa){
                        printf("Hay fosforos \n");
                        fumando++;
                        printf("Productor de papel fumando \n");
                    }else{
                    pthread_mutex_unlock((&mutFosf));
                    pthread_mutex_unlock(&mutPapel);
                    pthread_mutex_unlock(&mutTabaco);
                    }
                }else{
                    pthread_mutex_unlock(&mutPapel);
                    pthread_mutex_unlock(&mutTabaco);
                }
            }else{
                pthread_mutex_unlock(&mutTabaco);
            }
            if (fumando){
                    pthread_mutex_unlock(&mutFosf);
                    pthread_mutex_unlock(&mutTabaco);
                    pthread_mutex_unlock(&mutPapel);
                    tabEnMesa--;
                    papEnMesa--;
                    fosfEnMesa--;
                    sleep(2);
                    printed = 0;
                    printf("Productor de papel regreso de fumar \n");
                    espera = time(NULL) + 4;
                }
            }
    }
    pthread_exit(NULL);
}

void *fumarFosf(void *p){
    int fumando = 0;
    time_t espera = 0;
    fosfProducido = 0;
    fosfEnMesa = 0;
    int printed= 1;
    while(1){
            sleep(1);
        if(time(NULL) < espera){
            if (fosfProducido == 0){
                fosfProducido = 1;
                printf("Produje fosforos \n");
            }
        }else{
            if(!printed){
                printf("Productor de fosforos ya puede fumar de nuevo \n");
                printed = 1;
            }
            if (fosfProducido == 0){
                fosfProducido = 1;
                printf("Produje fosforos \n");
                }
            pthread_mutex_lock(&mutTabaco);
             if(tabEnMesa){
                printf("Hay tabaco \n");
                pthread_mutex_lock(&mutPapel);
                sleep(1);
                if(papEnMesa){
                        printf("Hay papel \n");
                    pthread_mutex_lock(&mutFosf);
                    sleep(1);
                    if(fosfEnMesa){
                        printf("Hay fosforos \n");
                        fumando++;
                        printf("Productor de fosforos fumando \n");
                    }else{
                    pthread_mutex_unlock((&mutFosf));
                    pthread_mutex_unlock(&mutPapel);
                    pthread_mutex_unlock(&mutTabaco);
                    }
                }else{
                    pthread_mutex_unlock(&mutPapel);
                    pthread_mutex_unlock(&mutTabaco);
                }
            }else{
                pthread_mutex_unlock(&mutTabaco);
            }
            if (fumando){
                    pthread_mutex_unlock(&mutFosf);
                    pthread_mutex_unlock(&mutTabaco);
                    pthread_mutex_unlock(&mutPapel);
                    tabEnMesa--;
                    papEnMesa--;
                    fosfEnMesa--;
                    sleep(2);
                    printed = 0;
                    printf("Productor de fosforos regreso de fumar \n");
                    espera = time(NULL) + 4;
                }
        }
    }
    pthread_exit(NULL);
}



int main()
{

    pthread_t agent;
    pthread_create(&agent, NULL,agente,NULL);
    pthread_t fumador1;
    pthread_t fumador2;
    pthread_t fumador3;
    pthread_create(&fumador1,NULL,fumarTab,NULL);
    pthread_create(&fumador2, NULL, fumarPap,NULL);
    pthread_create(&fumador3, NULL, fumarFosf,NULL);

    pthread_join(agent, NULL);
    pthread_join(fumador1, NULL);
    pthread_join(fumador2, NULL);
    pthread_join(fumador3, NULL);

}
