//
//  cliente.c
//  factorial_sockets
//
//  Created by Vicente Cubells Nonell on 28/09/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

//
//  cliente.c
//  sockets
//
//  Created by Vicente Cubells Nonell on 14/09/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//



#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define TCP_PORT 8003

int main(int argc, const char * argv[]) {

    struct sockaddr_in direccion;
    int * buffer = ( int *)malloc(sizeof(int));

    int cliente;

    int * lecturas = (int *)malloc(sizeof(int)*20);

    int leidos, escritos;

    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }

    //Crear el socket
    cliente = socket(PF_INET, SOCK_STREAM, 0);

    // Establecer conexión
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);

    int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));

    // Comunicación
    time_t t;

    srand((unsigned) time(&t));
    int seguir = 1;
    if (estado == 0) {
        printf("Conectado a %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));

        // Leer de teclado y escribir en socket
        while (seguir < 20) {

            for(int i = 0; i < 20 ; i ++){
            *(lecturas + i) = rand() % 40;

            }
            printf("primero: %d \n", *(lecturas));
            printf("Escribo en el buffer %d", lecturas);
            write(cliente, &buffer, lecturas);
            seguir++;
            sleep(2);
            printf("\n");
        }
    }
    free(lecturas);
    // Cerrar el socket
    close(cliente);

    return 0;
}

