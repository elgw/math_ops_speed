#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef void (*mop)(const double * restrict, const double * restrict , double * restrict , const size_t );

typedef struct{
  char * name;
  mop fun;
  double time;
} optest;


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



int main(int argc, char ** argv)
{

  size_t N = (size_t) 1e6;

  if(argc>1)
  {
    N = atol(argv[1]);
  }

  int nCycles = 10;
  N /= nCycles;

  optest tests[] = {
    {"plus",  op_plus,  0},
    {"minus", op_minus, 0},
    {"div",   op_div,   0},
    {"mult",  op_mult,  0},
    {"sqrt",  op_sqrt,  0},
    {"cbrt",  op_cbrt,  0},
    {"sin",   op_sin,   0},
    {NULL,    NULL,     0}
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

  printf("op \t time (s) \t norm time \t op/s\n");
  for(int idx = 0 ; idx<nTests; idx++)
  { 
    printf("%s \t %f \t %f \t %e\n", tests[idx].name, tests[idx].time, tests[idx].time/mintime, (nCycles*N)/tests[idx].time);
  }

  free(A);
  free(B);
  free(C);
  return 0;
}
