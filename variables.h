#define N_STAR 1000
#define M 1
#define G 1

typedef struct star{
    double r, v_r, v_t, m, U;
    int relaxed;
} star;

typedef struct vector{
    double x, y, z;
} vector;


double rng(void);
void givePos(star []);
void giveVel(star []);
double g_prob(double);

void sortStars(star []);
int compareRadii(const void *, const void *);
void updateShellPots(star []);

void relax(star, star, double);

double E_kin(star);
double E_tot(star []);

void newPos(star, double, double);
int find_k(star []);

void newPotential(star []);