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
    }
    int preC1 = rand() % 4999;
    int preC2 = rand() % 4999;
    float c1[2];
    float c2[2];
    float c1Ant[2];
    float c2Ant[2];

    c1[0] = datos[preC1][0];
    c1[1] = datos[preC1][1];


    c2[0] = datos[preC2][0];
    c2[1] = datos[preC2][1];

    float diffC1 = 10000;
    float diffC2 = 10000;
    float sumaC1[2];
    float sumaC2[2];


    while(diffC1 > 0.0001 && diffC2 > 0.0001){
        sumaC1[0] = 0;
        sumaC1[1] = 0;

        sumaC2[0] = 0;
        sumaC2[1] = 0;
        #pragma omp parallel for
        for(int i = 0; i < max; i++){
            float distC1 = (datos[i][0]-c1[0])/(datos[i][1] - c1[1]);
            float distC2 = (datos[i][0]-c2[0]) / (datos[i][1] - c2[1]);
            if(abs(distC1) < abs(distC2)){
                sumaC1[0] += datos[i][0];
                sumaC1[1] += datos[i][1];
            }else{
                sumaC2[0] += datos[i][0];
                sumaC2[1] += datos[i][1];
            }
        }
        c1Ant[0] = c1[0];
        c1Ant[1] = c1[1];
        c2Ant[0] = c2[0];
        c2Ant[1] = c2[1];

        c1[0] = sumaC1[0] / max;
        c1[1] = sumaC1[1] / max;
        c2[0] = sumaC2[0] / max;
        c2[1] = sumaC2[1] / max;

        diffC1 = (c1[0] - c1Ant[0]) / (c1[1] - c1Ant[1]);
        diffC2 = (c2[0] - c2Ant[0]) / (c2[1] - c2Ant[2]);
    }

    printf("C1 final = %f, %f \n", c1[0], c1[1]);
    printf("C2 final = %f, %f \n", c2[0], c2[1]);


    return 0;
}
