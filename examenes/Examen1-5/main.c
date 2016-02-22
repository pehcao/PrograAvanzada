//
//  main.c
//  factorial_sockets
//
//  Created by Vicente Cubells Nonell on 28/09/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define TCP_PORT 8003


void calculos(int * arreglo){
    int min = *(arreglo + 1);
    int max= *(arreglo + 1);
    int avg= *(arreglo + 1);
    int suma = 0;
    for(int i = 1; i < 20 ; i ++){
        if(*(arreglo + i) < min){
            min = *(arreglo + i);
        }
        if(*(arreglo + i ) > max){
            max = *(arreglo + i);
        }
        suma += *(arreglo + i);
    }

    printf("El minimo es: %d \n", min);
    printf("El maximo es: %d \n", max);
    printf("El promedio es: %d \n", suma /20);

}



int main(int argc, const char * argv[]) {

    struct sockaddr_in direccion;
    int * buffer;

    int servidor, cliente;

    int leidos, escritos;

    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }

    //Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);

    // Enlace con el socket
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);

    int a = bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));

    if(a != 0){
        printf("Mal bind \n");
    }
    // Escuchar a los clientes
    listen(servidor, 10);

    // Comunicación
    socklen_t tamano = sizeof(direccion);

    cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);

    int fact;

    if (cliente >= 0) {
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        // Leer de socket y escribir en pantalla
        int x = 0;
        int * dir;
        printf("Voy a leer \n");
        while (x < 20) {
            if(leidos = read(cliente, &buffer, sizeof(buffer))){
                dir= buffer + 8;
                printf("Lei del buffer %d \n", dir);
                printf("primero: %d \n", *(dir));
                if(dir == 0){
                    break;
                }
                x++;
                calculos(dir);
            }
        }
    }

    // Cerrar el socket

    close(servidor);
    close(cliente);

    return 0;
}
