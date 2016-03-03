#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int timeout = 2;
int c = 0;
int cont = 0;
int z = 0;

void manejador(int sig){
    if(sig == SIGINT){
        timeout++;
        c++;
    }
    else if(sig == SIGTSTP){
        if(timeout > 1){
            timeout--;
        }
        z++;
    }else if(sig == SIGALRM){
        printf("Aparezco cada %d segundos \n",timeout);
        alarm(timeout);
    }else if(sig == SIGUSR1){
        printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z. Acabando...\n",c,z);
        cont = 1;
    }
}

int main()
{
    int ppid = getpid();
    int pid = fork();
    if(pid > 0){
        printf("El timeout es de %d segundos %d\n", timeout,getpid());
        signal(SIGINT,manejador);
        signal(SIGTSTP,manejador);
        signal(SIGALRM,manejador);
        signal(SIGUSR1, manejador);
        alarm(timeout);
        while(!cont){

        }

        kill(getpgrp(), SIGKILL);
    }

    if (pid == 0){
        signal(SIGINT,SIG_IGN);
        signal(SIGTSTP,SIG_IGN);
        sleep(10);
        kill(ppid,SIGUSR1);
    }
}
