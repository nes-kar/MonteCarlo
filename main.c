#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "variables.h"

FILE *fp, *result;

star stars[N_STAR];

double E_kin(star);
double E_tot(star []);


int main(){
    int i, N_LOOP, k, j;
    double dt, a, b;

    fp = fopen("init.txt", "w"); 
    if (fp == NULL)
        exit(1);
    fprintf(fp, "#Mass\t #Pos\t #RadialVel\t #TransVel\t #Potential\n");

    srand(time(0));
    for (i = 0; i < N_STAR; i++){
        stars[i] = (star) {0, 0, 0, 0, 0, 0};
        stars[i].m = 1. / N_STAR;
    }

    givePos(stars);
    sortStars(stars);
    giveVel(stars);
    newPotential(stars);
    
    printf("Total energy of %d stars: %4.4f \n", N_STAR, E_tot(stars));

    for (i = 0; i < N_STAR; i++){
        fprintf(fp, "%9.4f\t %9.4f\t %9.4f\t %9.4f\t %9.4f\n", stars[i].m, stars[i].r,
        stars[i].v_r, stars[i].v_t, stars[i].U);
    }
    fclose(fp);


/*
    N_LOOP = 0;
    while (N_LOOP < 100){ // MAIN LOOP
        dt = 0.005 * (N_STAR / log(N_STAR)) * pow(M, 2.5) * pow(fabs(E_tot(stars)), -1.5);
        for (k = 0; k < N_STAR; k++){
            if (stars[k].relaxed)
                continue;
            else
                relax(stars[k], stars[k + 2], dt);
        }
        
        j = find_k(stars);
        a = (stars[j + 1].U - stars[j].U) / (1.0 / stars[j + 1].r - 1.0 / stars[j].r);
        b = (stars[j].U * (1.0 / stars[j + 1].r) - stars[j + 1].U * (1.0 / stars[j].r)) / (1.0 / stars[j + 1].r - 1.0 / stars[j].r);

        for (i = 0; i < N_STAR; i++){
            newPos(stars[i], a, b);
        }

        // ----------- 
        
        // Check for escaped stars

        // ----------

        sortStars(stars);

        for (i = 0; i < N_STAR; i++){
            stars[i].relaxed = 0;
        }

        N_LOOP++
        // Update N_STAR and M
    }
*/


}




double E_kin(star test){
    return test.m * (test.v_r * test.v_r + test.v_t * test.v_t) / 2.0;
}

double E_tot(star stars[N_STAR]){
    int i;
    double E = 0;
    
    for (i = 0; i < N_STAR; i++){
        E += E_kin(stars[i]) ;
    }
    return E;
}

// int * massRadii(star stars[N_STAR]){
//     double m;
//     static double r[10];

    

// }