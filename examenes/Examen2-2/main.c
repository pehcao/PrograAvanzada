#include <stdio.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

char * buffer[20];
FILE *archivo = NULL;
int grabar = 0;

void borrar()
{
  DIR *dir;
  struct dirent *d;
  dir = opendir("datos");
  char buf[256];
  while(d = readdir(dir))
  {
    if(d->d_type == DT_REG)
    {
      printf("Borrando %s\n", d->d_name);
      sprintf(buf, "%s/%s", "datos", d->d_name);
      unlink(buf);
      remove(buf);
    }
  }
}


void handler(int sig){
    printf("Alarma generada \n");
    grabar = 0;
}

int main()
{
    DIR* dir = opendir("datos");
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    signal(SIGALRM, handler);
    if (dir)
    {
        borrar();
    }else if (ENOENT == errno){
        mkdir("./datos", 0700);
    }else{
        printf("Error creando el directorio \n");
    }
    for(int i = 0; i < 5; i++){
        sprintf(buffer, "./datos/a%d",i);
        archivo = fopen(buffer, "w+");
        alarm(3);
        while(grabar)
            fputc('x', archivo);
        fclose(archivo);
        i++;
    }
    return 0;
}
