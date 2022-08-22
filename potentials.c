#include <stdlib.h>
#include <math.h>
#include "variables.h"

int compareRadii(const void *a, const void *b){
    star *S1 = (star *) a;
    star *S2 = (star *) b;
    if (S1->r < S2->r)
        return -1;
    else if (S1->r > S2->r)
        return 1;
    else
        return 0;
}


void sortStars(star stars[N_STAR]){
    qsort(stars, N_STAR, sizeof(star), compareRadii);
}

void updateShellPots(star stars[N_STAR]){
    double m_curr = M;
    int k;

    stars[N_STAR].r = INFINITY;
    stars[N_STAR].U = 0.0;

    for (k = N_STAR - 1; k >= 0; k--){
        stars[k].U = stars[k + 1].U - m_curr * (1.0 / stars[k].r - 1.0 / stars[k + 1].r);
        m_curr -= stars[k + 1].m;
    }
}

int findIndex(star stars[N_STAR], double dist){
    int i, index;
    i = index = 0;

    while (i < N_STAR){
        if (stars[i].r <= dist <= stars[i+1].r)
            break;
        else
            index++;
    }
    return index;
}

double U_r(star stars[N_STAR], double dist){
    int k;
    
    k = findIndex(stars, dist);
    return stars[k].U + (((1 / stars[k].r) - (1 / dist)) / ((1 / stars[k].r) - (1 / stars[k+1].r)))
            *(stars[k+1].U - stars[k].U);
}


void newPotential(star stars[N_STAR]){
    int i, j;
    double p, r;

    for (i = 0; i < N_STAR; i++){
        p = 0;
        for (j = 0; j < N_STAR; j++){
            if (i == j)
                continue;
            else{
                r = stars[i].r - stars[j].r;
                p += - stars[i].m * stars[j].m / sqrt(r*r);
            }
        }
        stars[i].U = p;
    }

}

