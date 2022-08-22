#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "variables.h"


double rng(void){
    return (double) rand() / (double) RAND_MAX;
}

void givePos(star stars[N_STAR]){
    int i;
    double x, R;

    for (i = 0; i < N_STAR ; i++){
        x = pow(rng(), -2.0/3.0);
        R = pow(x - 1, -0.5);
        stars[i].r = R;
    }
}

// Probability distribution
double g_prob(double q){ 
    return q * q * pow((1 - (q * q)), 3.5);
}

void giveVel(star stars[N_STAR]){
    int i, x4;
    double x1, x2, x3, v, v_z;
    
    for (i = 0; i < N_STAR; i++){
        x1 = rng();
        x2 = rng();
        while ((0.1 * x2) > g_prob(x1)){
            x1 = rng();
            x2 = rng();
        }
        v = x1 * sqrt(2) * pow(1 + stars[i].r * stars[i].r, -0.25);
        x3 = rng();
        x4 = (rng() < 0.5) ? -1 : 1;

        v_z = v * (1 - 2*x3);

        stars[i].v_r =  v_z;
        stars[i].v_t = x4 * pow(v * v - v_z * v_z, 0.5);

    }
}
