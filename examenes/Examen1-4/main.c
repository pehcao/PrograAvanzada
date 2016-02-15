#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void escribir(int * fd, int num){
    close(fd[0]);
     write(fd[1], &num, sizeof(int));
}

int leer(int *fd){
    int input;
    close(fd[1]);
    read(fd[0], &input, sizeof(int));
}


int main(int * argc, int * argv[])
{
    int c;
    int n;
     while ((c = getopt (argc, argv, "n:")) != -1){
        switch(c){
    case 'n':
        n = atoi(optarg);
        break;
        }
    }

    int ** tubos;
    tubos = (int **) malloc(sizeof(int)*n);
    int * pids;
    pids = (int *) malloc(sizeof(int)*n);
    int fd;
    int fds;

    int pid = getpid();
    int pidc;
    for(int i = 0; i < n; i++){
        if(pid == getpid()){
            *(tubos+i) = (int *) malloc(sizeof(int)*2);
            pipe(*(tubos+i));
            pidc= fork();
            if(pidc <0){
                printf("Error creando hijo \n");
            }else if(pidc > 0){
                *(pids + i) = pidc;
                if(i == n-1){
                    fd = *(tubos);
                    escribir(fd,5);
                }
            }else{
                int numero = i;
                fd = *(tubos + i);
            }
        }
    }
    printf("Tengo el pipe %d \n",fd);
    int estatus;
    int contar = 0;
    while(estatus = leer(fd)){
        contar++;
        if(estatus == 5){
            printf("Soy el hijo %d  y recibi el testigo\n", getpid());
            sleep(2);
            printf("Soy el hijo %d y mando el testigo \n",getpid());
            escribir(fd,5);
        }
    }
    printf("Saliendo \n");
    exit(0);
}
