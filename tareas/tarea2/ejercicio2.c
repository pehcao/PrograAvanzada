#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    time_t t;
    srand((unsigned) time(&t));
    int elementos = rand() % 50;
    printf("Se generaran %d elementos en el arreglo \n",elementos);
    int * arreglo = (int *)malloc(sizeof(int)*elementos);
    int num;
    printf("Los numeros a sumar son: \n");
    for(int i = 0; i< elementos; i++){
        num = rand() % 5;
        printf("%d  ",num);
        *(arreglo+i) = num;
    }
    printf("\n");
    int pid1 = fork();
    if(pid1 < 0){
        printf("Error creando hijo 1 \n");
    }else if(pid1 == 0){
        int resultado = 0;
        for (int i = 0; i < elementos /2;i++){
            resultado += *(arreglo+i);
        }
        printf("Suma del hijo1: %d \n",resultado);
        exit(resultado);
    }

    int pid2 = fork();

    if(pid2 < 0){
        printf("Error creando hijo 2 \n");
    }else if(pid2 == 0){
        int resultado = 0;
        for (int i = elementos; i > elementos/2;i--){
            resultado += *(arreglo+i);
        }
        printf("Suma del hijo2: %d \n", resultado);
        exit(resultado);
    }

    int total = 0;
    int status;
    for(int i = 0; i < 2 ; i++){
        wait(&status);
        printf("Termino un hijo con resultado de: %d \n", WEXITSTATUS(status));
        total += WEXITSTATUS(status);
    }
    printf("La suma de todos los numeros es: %d\n", total);
}
