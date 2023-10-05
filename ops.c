#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifdef __x86_64__
#include <x86intrin.h>
#define rdtsc_init()
uint64_t rdtsc(void)
{
    return __rdtsc();
}
#endif

double dtfactor = 1;

#ifdef __ARM_ARCH
// Constant rate timer
uint64_t get_cntvct(void)
{
    uint64_t val;
    __asm__ volatile("mrs %0, cntvct_el0" : "=r" (val));
    return val;
}

// The the clock of the timer
uint64_t get_cntfrq(void)
{
  uint64_t val;
  __asm__ volatile("mrs %0, cntfrq_el0" : "=r"(val));
  return val;
}

// The clock of the CPU
uint64_t get_cpufreq(void)
{
  char file[] = "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq";
  FILE * fid = fopen(file, "r");
  if(fid == NULL)
    {
      fprintf(stderr, "Can't open %s\n", file);
      return 0;
    }
  char * buf = malloc(128);
  size_t nread = fread(buf, 1, 127, fid);
  fclose(fid);
  buf[nread] = '\0';
  size_t val = atol(buf);
  free(buf);
  return val;
}



void rdtsc_init()
{
    uint64_t cpufreq = get_cpufreq();
    uint64_t cntfreq = get_cntfrq();
    dtfactor = cpufreq / cntfreq;
}

#define rdtsc get_cntvct

#endif

#include <stdint.h>

typedef void (*mop)(const double * restrict,
                    const double * restrict ,
                    double * restrict ,
                    const size_t );

typedef struct{
    char * name;
    mop fun;
    double time;
    uint64_t nCycles;
} optest;

int
cmp_optest_time(const void * A, const void * B)
{
    optest * opA = (optest *) A;
    optest * opB = (optest *) B;

    if(opA->time > opB->time)
        return 1;
    if(opA->time < opB->time)
        return -1;
    return 0;
}

void
hline(int w)
{
    for(int kk = 0; kk<w; kk++)
    {
        printf("\x1b(0%c\x1b(B", (int) 0x71 );
    }
    printf("\n");
    return;
}

static double
clockdiff(struct timespec* start, struct timespec * finish)
{
    double elapsed = (finish->tv_sec - start->tv_sec);
    elapsed += (finish->tv_nsec - start->tv_nsec) / 1000000000.0;
    return elapsed;
}


#define ops_cat(x) op_ ## x

/* For operators taking one argument */
#define op1(x)                                                          \
    void                                                                \
    ops_cat(x) (const double * restrict A,                              \
                __attribute__ ((unused)) const double * restrict B,     \
                double * restrict C,                                    \
                const size_t N)                                         \
    {                                                                   \
        for(size_t kk = 0; kk < N; kk++)                                \
            C[kk] = x (A[kk]);                                          \
    }

/* For operators taking two arguments */
#define op2(x)                                  \
    void                                        \
    ops_cat(x) (const double * restrict A,      \
                const double * restrict B,      \
                double * restrict C,            \
                const size_t N)                 \
    {                                           \
        for(size_t kk = 0; kk < N; kk++)        \
            C[kk] = x (A[kk], B[kk]);           \
    }

/* For built in operators */
#define opb(ONAME, OSYMBOL)                     \
    void                                        \
    ops_cat(ONAME) (const double * restrict A,  \
                    const double * restrict B,  \
                    double * restrict C,        \
                    const size_t N)             \
    {                                           \
        for(size_t kk = 0; kk < N; kk++)        \
            C[kk] = A[kk] OSYMBOL B[kk];        \
    }


op1(sqrt);
op1(sqrtf);
op1(cbrt);
op1(sin);
op1(sinf);
op1(j0);
op1(j1);
op1(asin);
op1(sinh);
op1(log);
op1(log10);

op1(exp);
op1(tan);
op1(atan);
op1(tanh);
op1(round);
op1(nearbyint);
op1(ceil);
op1(floor);
op1(isinf);
op1(isnan);
op1(isnormal);

op2(pow);
op2(powf);
op2(copysign);

opb(plus, +);
opb(minus, -);
opb(div, /);
opb(mult, *);


void
op_max(const double * restrict A,
       const double * restrict B,
       double * restrict C,
       const size_t N) {
    for(size_t kk = 0; kk < N; kk++)
    {
        if(A[kk] > B[kk])
        {
            C[kk] = A[kk];
        } else {
            C[kk] = B[kk];
        }
    }
}


__attribute__ ((malloc)) double *
double_rand(const size_t N, const double max)
{
    double * x = calloc(N, sizeof(double));
    for(size_t kk = 0; kk<N; kk++)
    {
        x[kk] = 1e99 + max * (double) rand() / (double) RAND_MAX;
    }
    return x;
}

int main(int argc, char ** argv)
{

    size_t N = (size_t) 1e5;

    if(argc>1)
    {
        N = atol(argv[1]);
    }

    int nRepeats = 10;

    optest tests[] = {
        {"plus",      op_plus,      0, 0},
        {"minus",     op_minus,     0, 0},
        {"div",       op_div,       0, 0},
        {"mult",      op_mult,      0, 0},
        {"sqrt",      op_sqrt,      0, 0},
        {"sqrtf",     op_sqrtf,     0, 0},
        {"cbrt",      op_cbrt,      0, 0},
        {"sin",       op_sin,       0, 0},
        {"sinf",      op_sinf,      0, 0},
        {"asin",      op_asin,      0, 0},
        {"sinh",      op_sinh,      0, 0},
        {"log",       op_log,       0, 0},
        {"j0",        op_j0,        0, 0},
        {"j1",        op_j1,        0, 0},
        {"log10",     op_log10,     0, 0},
        {"copysign",  op_copysign,  0, 0},
        {"pow",       op_pow,       0, 0},
        {"powf",      op_powf,      0, 0},
        {"exp",       op_exp,       0, 0},
        {"tan",       op_tan,       0, 0},
        {"atan",      op_atan,      0, 0},
        {"round",     op_round,     0, 0},
        {"nearbyint", op_nearbyint, 0, 0},
        {"isnormal",  op_isnormal,  0, 0},
        {"isnan",     op_isnan,     0, 0},
        {"isinf",     op_isinf,     0, 0},
        {"ceil",      op_ceil,      0, 0},
        {"floor",     op_floor,     0, 0},
        {"'max'",     op_max,       0, 0},
        {NULL,        NULL,         0, 0},
    };

    int nTests = 0;
    while(tests[nTests].name != 0)
    { nTests++; }

    double * A = double_rand(N, 1.0);
    double * B = double_rand(N, 1.0);
    double * C = calloc(N, sizeof(double));

    struct timespec ts, te;

    // Warm up
    // - get cache state in order
    // - spin up the CPU with stress -t 1 first
    tests[0].fun(A,B,C, N);

    for(int kk = 0; kk<nRepeats; kk++)
    {
        rdtsc_init();
        for(int idx = 0 ; idx<nTests; idx++)
        {
            // TODO: Either the time measurement or the
            //       cycle measurement will be screwed if we try to do both at
            //       the same time
            tests[idx].nCycles = rdtsc();
            clock_gettime(CLOCK_REALTIME, &ts);
            tests[idx].fun(A,B,C,N);
            clock_gettime(CLOCK_REALTIME, &te);
            tests[idx].nCycles = (rdtsc() - tests[idx].nCycles) * dtfactor;
            tests[idx].time += clockdiff(&ts, &te);
        }
    }
    printf("\n");

    double mintime = 99e99;
    for(int idx = 0 ; idx<nTests; idx++)
    {
        if(tests[idx].time < mintime)
        { mintime = tests[idx].time; }
    }

    qsort(tests, nTests, sizeof(optest), cmp_optest_time);

    printf("%10s %10s %10s %11s %10s\n",
           "operator", "time (s)", "rel. time", "op/s", "cyc/op");
    hline(58);
    for(int idx = 0 ; idx<nTests; idx++)
    {
        printf("%10s %10.6f %10.6f %11.3e %10.3f\n",
               tests[idx].name,
               tests[idx].time,
               tests[idx].time/mintime,
               (nRepeats*N)/tests[idx].time,
               (double) tests[idx].nCycles/ (double) (nRepeats*N));
    }

    free(A);
    free(B);
    free(C);
    return EXIT_SUCCESS;
}
