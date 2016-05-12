/*
 * PROYECTO PROGRAMACION AVANZADA
 *
 * Miguel del Moral
 * Erick Rivas
 * Enrique Paullada
 * Alejandro Herce
 *
 */

#include <iostream>
#include <unistd.h>
#include <omp.h>
#include <bitset>
#include <string>
#include <limits>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

#define N    100000

using namespace std;

typedef struct params{
    int inicio;
    int fin;
};

string dec2bin(double);
double bin2dec(string);
vector<double> merge(double, double);
double mutate(double);
 pair<int, double> ranks[N];
bool found = false;
    double data[N];
    double A;
    double D;

void * threadPart(void * p){
    params pars = *((params *) p);
    int i = pars.inicio;
    int f = pars.fin;
    for (; i < f; i++)
        {
            double rank = pow(D - data[i], 2) / 2;
            ranks[i] = make_pair(i, rank);

            //Si el ranking es menor que 0.0001 termina el programa
            if (rank < 0.0001 && !found)
                {
                    cout << "Result: " << data[i] << endl;
                    found = true;
                }
        }
}

// -------------- MAIN --------------

int main()
{
    time_t inicio;
    time(&inicio);
    int    MAX;
    pthread_t threads[10];
    cin >> A;
    MAX = (int)A;
    D   = sqrt(A);
    int lim = N /10;

    //Población aleatoria

    srand(time(NULL));
    for (int i = 0; i < N; i++)
        data[i] = rand() % MAX + ((rand() % 1000) / 1000.0);

    double lastError = pow(MAX,2);

    while (!found)
    {

        for(int i = 0; i < 10; i++){
            params * arg = (params *) malloc(sizeof(params));
            (*arg).fin = lim*i + lim;
            (*arg).inicio = lim*i;
            pthread_create(&threads[i],NULL,threadPart,arg);
        }

        for(int i = 0; i < 10; i++){
            pthread_join(threads[i],NULL);
        }

        //Obtención de rankings

        if (found) break;


        /*
         * for (int i = 0; i < N; i++){
         *  cout << "N: " << data[ranks[i].first] << " E: " << ranks[i].second << endl;
         * }
         * cout << "----";
         */


        //Sort
        for (int j = 0; j < N; j++)
            for (int i = 0; i < N; i++)
                if (ranks[j].second < ranks[i].second)
                {
                    pair<int, double> temp = ranks[i];
                    ranks[i] = ranks[j];
                    ranks[j] = temp;
                }

        printf("it :: mejor %f\n",ranks[0].second);


        //Merge
        int    combined = 0;
        double temp     = -1;

        while (combined < N / 2)
        {
            for (int i = 0; i < N / 2 && combined < N / 2; i++)
            {
                if (rand() % 10 < 7)
                {
                    int pos = ranks[i].first;
                    if (temp == -1)
                    {
                        temp = data[pos];

                    }
                    else
                    {
                        vector<double> result = merge(temp, data[pos]);
                        temp = -1;

                        int posSus1 = ranks[N / 2 + combined].first;
                        int posSus2 = ranks[N / 2 + combined + 1].first;
                        data[posSus1] = result[0];
                        data[posSus2] = result[1];
                        combined      +=2;
                    }
                }
            }
        }

        for (int i = 0; i < N; i++)
            if (rand() % 10 < 2)
                data[i] = mutate(data[i]);


        if (abs(lastError - ranks[0].second) < 0.00001){
            MAX = data[ranks[0].first];
            for (int i = 0; i < N; i++)
                data[i] = rand() % MAX + ((rand() % 10000) / 1000.0);
        }


    }

    time_t fin;
    time(&fin);

    cout << "Tiempo: " << fin - inicio << "\n";
    return 0;
}



// -------------- FUNCIONES SUPER IMPORTANTES --------------

string dec2bin(double input){
    string res = "";
    double n   = 524288;

    for (int i = 0; i < 40; i++){
        if (n == .5)
            res += ".";
        if (input >= n){
            res   += "1";
            input -= n;
        }else{
            res += "0";
        }
        n /= 2;
    }
    return res;
}

double bin2dec(string input){
    double res = 0;
    double n   = 524288;

    for (int i = 0; i < 40; i++){
        if (input[i] == '.')
            i++;
        if (input[i] == '1')
            res += n;
        n /= 2;
    }
    return res;
}

vector<double> merge(double a, double b){
    string         s1   = dec2bin(a);
    string         s2   = dec2bin(b);
    int            pos  = rand() % 20;
    int            posd = rand() % 20;
    string         n1   = s1.substr(0, pos) + s2.substr(pos, 20 - pos) + "." + s1.substr(21, posd) + s2.substr(21 + posd, 20 - posd);
    string         n2   = s2.substr(0, pos) + s1.substr(pos, 20 - pos) + "." + s2.substr(21, posd) + s1.substr(21 + posd, 20 - posd);

    vector<double> arr;
    arr.push_back(bin2dec(n1));
    arr.push_back(bin2dec(n2));
    return arr;
}

double mutate(double num){
    double res;
    string ericIsGay = dec2bin(num);

    for (int i = 0; i < ericIsGay.length(); i++)
        if (ericIsGay[i] == '1')
            ericIsGay[i] = '0';
        else if (ericIsGay[i] == '0')
            ericIsGay[i] = '1';
    return bin2dec(ericIsGay);
}
