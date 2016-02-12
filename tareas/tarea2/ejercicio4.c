#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void crear(int actual, int procesos, int niveles){
    for(int i = 0; i< actual; i++){
         printf("\t");
    }
    printf("%d \n",getpid());
    int pid;
    for(int i = 0; i < procesos; i++){
        pid = fork();

        if(pid < 0){
            printf("Error creando hijo, terminando ejecucion \n");
            exit(0);
        }else if(pid > 0){
            int status;
            for(int j = 0; j < procesos; j++){
                wait(&status);
            }
        }else{
            if(actual < niveles){
                crear(actual + 1,procesos,niveles);
            }
        }
    }
    exit(0);
}

int main(int argc, const char * argv[])
{
    int n;
    int p;
    int c;

    while ((c = getopt (argc, argv, "n:p:")) != -1){
        switch(c){
    case 'n':
        n = atoi(optarg);
        break;

    case 'p':
        p = atoi(optarg);
        break;
        }
    }
    crear(0,p,n);
    return 0;
}
