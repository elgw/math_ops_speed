#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

typedef void (*mop)(const double * restrict, const double * restrict , double * restrict , const size_t );

typedef struct{
  char * name;
  mop fun;
  double time;
} optest;

void hline(int w)
{
  for(int kk = 0; kk<w; kk++)
  {
    printf("\x1b(0%c\x1b(B", (int) 0x71 );
  }
  printf("\n");
  return;
}


static double clockdiff(struct timespec* start, struct timespec * finish)
{
  double elapsed = (finish->tv_sec - start->tv_sec);
  elapsed += (finish->tv_nsec - start->tv_nsec) / 1000000000.0;
  return elapsed;
}

void op_plus(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = A[kk] + B[kk]; 
}

void op_minus(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = A[kk] - B[kk]; 
}

void op_div(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = A[kk] / B[kk]; 
}

void op_mult(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = A[kk] * B[kk]; 
}

void op_sqrt(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = sqrt(A[kk]); 
}

void op_cbrt(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = cbrt(A[kk]); 
}

void op_sin(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = sin(A[kk]); 
}

void op_asin(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = asin(A[kk]); 
}

void op_sinh(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = sinh(A[kk]); 
}

void op_log(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = log(A[kk]); 
}

void op_log10(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = log10(A[kk]); 
}

void op_copysign(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = copysign(A[kk], B[kk]); 
}

void op_pow(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = pow(A[kk], B[kk]); 
}

void op_exp(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = exp(A[kk]); 
}

void op_tan(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = tan(A[kk]); 
}

void op_atan(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = tan(A[kk]); 
}

void op_tanh(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = tanh(A[kk]); 
}

void op_round(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = round(A[kk]); 
}

void op_nearbyint(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = nearbyint(A[kk]); 
}

void op_ceil(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = ceil(A[kk]); 
}

void op_floor(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = floor(A[kk]); 
}

/* Operations that have to be typecasted */

void op_isnormal(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = (int) isnormal(A[kk]); 
}

void op_isnan(const double * restrict A, const double * restrict B, double * restrict C, const size_t N) {
  for(size_t kk = 0; kk < N; kk++)
    C[kk] = (int) isnan(A[kk]); 
}


int main(int argc, char ** argv)
{

  size_t N = (size_t) 1e5;

  if(argc>1)
  {
    N = atol(argv[1]);
  }

  int nCycles = 10;

  optest tests[] = {
    {"plus",      op_plus,     0},
    {"minus",     op_minus,    0},
    {"div",       op_div,      0},
    {"mult",      op_mult,     0},
    {"sqrt",      op_sqrt,     0},
    {"cbrt",      op_cbrt,     0},
    {"sin",       op_sin,      0},
    {"asin",      op_sin,      0},
    {"sinh",      op_sinh,     0},
    {"log",       op_log,      0},
    {"log10",     op_log10,    0},
    {"copysign",  op_copysign, 0},
    {"pow",       op_pow,      0},
    {"exp",       op_exp,      0},
    {"tan",       op_tan,      0},
    {"atan",      op_tan,      0},
    {"round",     op_round,     0},
    {"nearbyint", op_nearbyint,     0},
    {"isnormal",  op_isnormal, 0},
    {"isnan",     op_isnan,    0},
    {"ceil",      op_ceil,     0},
    {"floor",     op_floor,    0},
    {NULL,        NULL,        0},
  };

  int nTests = 0;
  while(tests[nTests].name != 0)
  { nTests++; }

  double * A = malloc(N*sizeof(double));
  double * B = malloc(N*sizeof(double));
  double * C = calloc(N, sizeof(double));

  for(size_t kk = 0; kk<N; kk++)
  {
    A[kk] = (double) rand() / (double) RAND_MAX;
    B[kk] = 1e-99 + (double) rand() / (double) RAND_MAX;
  }

  struct timespec ts, te;
  //  timespec_get(&ts, TIME_UTC);


  // Warm up 
  // - get cache state in order
   tests[0].fun(A,B,C, N); 

  for(int kk = 0; kk<nCycles; kk++)
  {
    printf("."); fflush(stdout);
  for(int idx = 0 ; idx<nTests; idx++)
  { 
    clock_gettime(CLOCK_REALTIME, &ts);
    tests[idx].fun(A,B,C,N);
    clock_gettime(CLOCK_REALTIME, &te);
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

  printf("%10s %10s %10s %14s\n", "operator", "time (s)", "rel. time", "ops/s");
  hline(47);
  for(int idx = 0 ; idx<nTests; idx++)
  { 
    printf("%10s %10.6f %10.6f %14.6e\n", tests[idx].name, tests[idx].time, tests[idx].time/mintime, (nCycles*N)/tests[idx].time);
  }

  free(A);
  free(B);
  free(C);
  return 0;
}
