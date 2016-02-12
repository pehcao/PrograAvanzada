#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int nums;
    printf("¿Cuantos procesos quieres crear?");
    scanf("%d", &nums);
    time_t t;
    time_t now;
    int cid = getpid();
    for(int i = 0; i < nums; i++){
        if(cid > 0){
            cid = fork();
            if(cid > 0){
            printf("Se creo hijo %d \n", cid);
            }
        }
    }
    int status;
    if(cid == 0){
        srand((unsigned) getpid());
        int ran = rand() % 10;
        printf("Hijo %d durmiendo", getpid());
        printf("%d segundos \n ", ran);
        sleep(ran);
        exit(0);
    }else{
        for(int i = 0; i < nums; i++){
            printf("El hijo %d termino \n" ,wait(&status));
        }
    }
    return 0;
}
