#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void escribir(int * fd, int num){
    int f;
    close(*(fd));
    f = write(*(fd+1), &num, sizeof(int));
}

int leer(int *fd){
    int input;
    close(*(fd+1));
    read(*(fd), &input, sizeof(int));
    return input;
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
    *(tubos) = (int *) malloc(sizeof(int)* 2);
    escribir(*(tubos),-1);
    for(int i = 1; i < n; i++){
        if(pid == getpid()){
            *(tubos+i) = (int *) malloc(sizeof(int)*2);
            pipe(*(tubos+i));
            pidc= fork();
            if(pidc < 0){
                printf("Error creando hijo \n");
            }else if(pidc > 0){
                escribir((*tubos+i),-1);
                *(pids + i) = pidc;
                if(i == n-1){
                    fd = *(tubos);
                    fds = *(tubos + n-1);
                    escribir(fds,5);
                    }
            }else{
                int numero = i;
                fd = *(tubos + i);
                fds = *(tubos + i - 1);
            }
        }
    }
    printf("%d Tengo el pipe de entrada %d \n",getpid(),fd);
    printf("%d Tengo el pipe de salida %d \n \n",getpid(), fds);
    int estatus;
    while(1){
        estatus = leer(fd);
        sleep(2);
        if(estatus == 5){
            printf("Soy el hijo %d  y recibi el testigo %d \n \n", getpid(), estatus);
            sleep(2);
            printf("Soy el hijo %d y mando el testigo %d \n \n",getpid(), estatus);
            escribir(fds,5);
            escribir(fd,-1);
        }
    }
    free(fd);
    free(fds);
    printf("Saliendo \n");
    exit(0);
}
