#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc , const char * argv[])
{
    int c;
    int i = 0;
    int num;
    char * programa = (char * )malloc(sizeof(char)*50);
    while((c = getopt(argc,argv,"n:p:"))!= -1){
        switch(c){
            case 'n':
            num = atoi(optarg);
            i += 3;
            break;
            case 'p':
            strcpy(programa,optarg);
        }
        i++;
    }
    if(!num){
        printf("El parametro -n debe ser mayor que 0 \n");
        return 0;
    }
    int id;
    int idp = getpid();
    for(int i = 0; i < num ; i++){
        if(idp == getpid()){
            id = fork();
            if(id == -1){
                printf("Error creando hijo %d\n", i);
            }
        }
    }

    if(id > 0){
            int status;
            for (int i = 0; i< num ; i++){
                id = wait(&status);
                if(status == -1){
                    printf("Error ejecutando el programa en el hijo: %d \n", id);
            }
        }
    }else{
        int status;
        status = system(programa);
        printf("\n");
        free(programa);
        exit(status);
    }

    free(programa);
    return 0;
}
