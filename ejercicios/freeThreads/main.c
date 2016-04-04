#include <stdio.h>
#include <pthread.h>



typedef struct{
    char * type;
    void * val;
}params;
pthread_key_t var;

void destructor(void* args)
{
    params * p = (params *)args;
    if (p->type == "int*") {
        delete[] args;
    }
    if(p->type == "char*"){
        delete[] args;
    }
}

void * Hilo1(void * id)
{
    char* valor;
    int res;
    params p;
    if((valor = (char*)pthread_getspecific(var)) == NULL)
    {
        valor = new char[10];
        valor = "hola";
        p.type = "char *";
        p.val = valor;

    }
    res = pthread_setspecific(var,&p);

    printf("En el hilo 1 var = %s \n", (char *) pthread_getspecific(var));
    printf("TID1 en hilo 1 = %ld\n", pthread_self());
}


void * Hilo2(void * id)
{
    int* valor;
    int res;
    params p;
    if((valor = (int*)pthread_getspecific(var)) == NULL)
    {
        valor = new int(50);
        p.type= "int *";
        p.val = valor;

    }
    res = pthread_setspecific(var, &p);

    printf("En el hilo 1 var = %i \n", *(int*) pthread_getspecific(var));
    printf("TID1 en hilo 1 = %ld\n", pthread_self());
}

int main(int argc, char **argv)
{
    pthread_t tid1, tid2;

    pthread_key_create(&var, destructor);

    pthread_create(&tid1, NULL, Hilo1, NULL);
    printf("TID1 = %ld\n", tid1);

    pthread_create(&tid2, NULL, Hilo2, NULL);
    printf("TID2 = %ld\n", tid2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
