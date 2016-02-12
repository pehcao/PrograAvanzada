#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int id;
    int numero = 0;
    int status;
    int exitval;
    while(1){
        printf("Introduce un numero o 0 para salir\n");
        scanf("%d",&numero);
        if(numero < 1){
            break;
        }
        id = fork();
        if(id < 0){
            printf("Error creando proceso hijo");
        }else if (id > 0){
            printf("Proceso %d creado \n", id);
            exitval = wait(&status);
            printf("Proceso %d termino \n", exitval);
        }
        else if(id == 0){
            int resultado = 1;
            for(int i = 2; i <= numero; i++){
                    resultado*= i;
            }
            printf("El factorial de %d es: %d \n",numero,resultado);
            exit(0);
        }
        printf("\n \n");
    }
    return 0;
}
