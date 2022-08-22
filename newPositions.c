#include <stdio.h>
#include "variables.h"
#include <math.h>

double Q(star test){
    double E, L;
    E = (test.v_t * test.v_t + test.v_r * test.v_r) / 2.0;
    L = test.r * test.v_t;

    return 2*E - (L * L / (test.r * test.r));

}

double dQdr(double r, double L, double a){
    return (2 * L * L / (r*r*r)) + (2 * a / (r*r));
}

double drds(double r_max, double r_min, double s){
    return (r_max - r_min) * (3 - 3 * s * s) / 4.0;
}

double g(star test, double r_max, double r_min, double s){
    return pow(Q(test), -0.5) * drds(r_max, r_min, s);
}

int find_k(star stars[N_STAR]){
    int k;

    for (k = 0; k < N_STAR; k++){
        if ((Q(stars[k]) < 0) && (0 < Q(stars[k + 1])))
            break;
    }
    return k;
}

void newPos(star test, double a, double b){
    double E, L, r_min, r_max, x, F, g_m, g_p, s_0, g_0, X, r;

    E = E_kin(test) + test.U;
    L = test.r * test.v_t;

    x = -a + pow(a*a - (2*L*L*(b - E)), 0.5);

    r_min = L * L / x;
    r_max = x / (2 * (b - E));

    g_m = pow(3*(r_max - r_min) / dQdr(r_min, L, a), 0.5); // g(-1)
    g_p = pow(-3*(r_max - r_min) / dQdr(r_max, L, a), 0.5); // g(1)

    F = 1.2 * fmax(g_m, g_p);
    
    s_0 = -1 + 2 * rng();
    g_0 = F * rng();

    while (g_0 > g(test, r_max, r_min, s_0)){
        s_0 = -1 + 2 * rng();
        g_0 = F * rng();
    }

    r = ((r_min + r_max) / 2.0) + (r_max - r_min) * (3 * s_0 - s_0*s_0*s_0) / 4.0;
    test.r = r;

    X = (rng() > 0.5) ? -1 : 1;
    test.v_r = X * pow(Q(test), 0.5); // ?????
    test.v_t = L / r;
}
