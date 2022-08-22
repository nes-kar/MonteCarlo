#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include "variables.h"


vector addVectors(int n, vector a, vector b, ...){
    va_list args;
    va_start(args, b);

    vector c = (vector) {0, 0, 0};
    vector temp;
    int i = 0;
    while (i < n){
        temp = va_arg(args, vector);
        c.x += temp.x;
        c.y += temp.y;
        c.z += temp.z;
        i++;
    }
    va_end(args);
    return c;

}
vector negativeVector(vector a){
    return (vector) {-a.x, -a.y, -a.z};
}

vector scalarMult(vector a, double b){
    return (vector) {a.x * b, a.y * b, a.z * b};
}

double mod(vector a){
    return pow(a.x * a.x + a.y * a.y + a.z * a.z, 0.5);
}

void relax(star test, star field, double dt){
    double phi, delta_r, r, l, l_0, beta, w_p, Psi;
    vector w, w_1, w_2, w_new, v_test, v_field, v_test_new, v_field_new;

    phi = 2*M_PI*rng();
    v_test = (vector) {test.v_t, 0, test.v_r};
    v_field = (vector) {field.v_t * cos(phi), field.v_t * sin(phi), field.v_r};

    w = (vector) {field.v_t * cos(phi) - test.v_t, field.v_t * sin(phi),
                  field.v_r - test.v_r};
    
    delta_r = fabs(field.r - test.r);
    r = (test.r + field.r) / 2.0;
    l = pow((mod(w) * dt * log(N_STAR) / (2*r*r*delta_r)), -0.5);
    l_0 = G * (test.m + field.m) / (mod(w) * mod(w));

    beta = 2 * atan(l_0 / l);
    Psi = 2*M_PI*rng();

    w_p = pow(w.x*w.x + w.y*w.y, 0.5);

    w_1 = (vector) {w.y * mod(w) / w_p, - w.x * mod(w) / w_p, 0};
    w_2 = (vector) {- w.x * w.z / w_p, - w.y * w.z / w_p, w_p};

    w_new = addVectors(3, scalarMult(w, cos(beta)), 
                    scalarMult(w_1, sin(beta) * cos(Psi)),
                    scalarMult(w_2, sin(beta) * sin(Psi)));
    v_test_new = addVectors(3, v_test, 
                 negativeVector(scalarMult(w_new, field.m / (test.m + field.m))),
                 scalarMult(w, field.m / (test.m + field.m)));
    v_field_new = addVectors(3, v_field, 
                negativeVector(scalarMult(w, test.m / (test.m + field.m))),
                scalarMult(w_new, test.m / (test.m + field.m)));

    test.v_r = v_test_new.z;
    test.v_t = pow(v_test_new.x * v_test_new.x + v_test_new.y * v_test_new.x, 0.5);

    field.v_r = v_field_new.z;
    field.v_t = pow(v_field_new.x * v_field_new.x + v_field_new.y * v_field_new.x, 0.5);

    test.relaxed = 1;
    field.relaxed = 1;
}
