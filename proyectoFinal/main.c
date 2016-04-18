#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    int max = 5000;
    float datos[max][2];
    srand(time(NULL));

    #pragma omp parallel for
        for(int i = 0; i < max; i++){
            datos[i][0] = (rand()%10000);
            datos[i][0] /= 10000;
            datos[i][1] =  (rand()%10000);
            datos[i][1] /= 10000;
            printf("%f \n", datos[i][0]);
    }
    float preC1 = rand() % 4999;
    float preC2 = rand() % 4999;
    float c1[2];
    float c2[2];
    float c1Ant[2];
    float c2Ant[2];

    c1[0] = datos[preC1][0];
    c1[1] = datos[preC1][1]:


    c2[0] = datos[preC2][0];
    c2[1] = datos[preC2][1]:

    c1Ant = c1;
    c2Ant = c2;

    float diffC1 = 10000;
    float diffC2 = 10000;
    float distancias[5000][1][2];

    while(diffC1 > 0.0001 && diffC2 > 0.0001){
        #pragma omp parallel for private
        for(int i = 0; i < max; i++){
            float distC1 = (datos[i][0]-c1[0])/(datos[i][1] - c1[1]);
            float distC2 = (datos[i][0]-c2[0]) / (datos[i][1] - c2[1]));

            if(abs(distC1) < abs(distC2)){
                distancias[i][0] = distC1;
            }

        }
    }



    return 0;
}
