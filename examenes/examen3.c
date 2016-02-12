#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char * argv[])
{
   int numero;
    int c;
   while ((c = getopt (argc, argv, "n:")) != -1){
        switch(c){
    case 'n':
        numero = atoi(optarg);
        break;
    }
   }

    int id;
    int * hijos = (int*)malloc(sizeof(int) * numero);

    for(int i = 0; i < numero;i++){
        id = fork();
        if(id < 0){
            printf("Error creando hijo \n Se crearon %d \n", i);
        }else if(id >0){
            *(hijos + i) = id;
        }else{
            int promedio = (getpid() + getppid()) / 2;
            printf("Hijo %d \n Promedio: %d \n", getpid(), promedio);
            free(hijos);
            exit(0);
        }
    }
    int status;
    sleep(2);
    for (int i = 0; i < numero; i++){
        id = waitpid(*(hijos + i),&status,0);
        printf("Hijo %d acaba de terminar \n", id);
    }
    free(hijos);
    printf("Todos los hijos terminaron, terminando ejecucion del programa \n");
    return 0;
}
