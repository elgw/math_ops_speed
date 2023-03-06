# Tests the speed of common mathematical operations

Here is an attempt to benchmark common mathematical functions.

Please note that:

 * For some operators/functions the speed changes with the
   values of the inputs. Change the code to match whatever
   range that is of interest for you.

 * There might be more clever ways to time the commands.

 * When the arrays are larger than the L3-cache size,
   speed is capped.

 * The operators are called within a double loop-which has some overhead.
   That is not compensated for.

 * Surprises: `cbrt` vs `sqrt` as well as `round` vs `nearbyint`.

## Usage
Tested on Ubuntu 22.04, no special dependencies besides a compiler. To
spin up the cpu a command like `stress` could be used.

``` shell
make
stress -t 1 -c 1; ./ops
```

## Results

```
AMD Ryzen 7 3700X 8-Core Processor

  operator   time (s)  rel. time        op/s     cyc/op
──────────────────────────────────────────────────────────
     isnan   0.000164   1.000000   6.115e+09      0.059
 nearbyint   0.000164   1.000874   6.110e+09      0.059
      mult   0.000231   1.414469   4.323e+09      0.084
     'max'   0.000232   1.421691   4.301e+09      0.084
     minus   0.000235   1.435927   4.259e+09      0.083
      plus   0.000244   1.492197   4.098e+09      0.083
  copysign   0.000252   1.538910   3.974e+09      0.083
  isnormal   0.000257   1.570396   3.894e+09      0.093
      ceil   0.000269   1.642675   3.723e+09      0.097
     floor   0.000271   1.659064   3.686e+09      0.097
       div   0.000299   1.829177   3.343e+09      0.107
     isinf   0.000710   4.338680   1.409e+09      0.255
      sqrt   0.002010  12.291136   4.975e+08      0.746
     round   0.002827  17.287882   3.537e+08      1.019
      powf   0.003088  18.883179   3.238e+08      1.098
       log   0.003894  23.814617   2.568e+08      1.395
       exp   0.004944  30.235636   2.022e+08      1.778
      atan   0.006559  40.108058   1.525e+08      2.377
       pow   0.006588  40.288622   1.518e+08      2.366
     log10   0.007011  42.869970   1.426e+08      2.525
      sinh   0.007096  43.394510   1.409e+08      2.550
      asin   0.007125  43.568286   1.404e+08      2.570
      cbrt   0.011627  71.102163   8.600e+07      4.191
       sin   0.034938 213.647684   2.862e+07     12.548
       tan   0.039110 239.159822   2.557e+07     14.135
        j0   0.089347 546.355930   1.119e+07     32.118
        j1   0.091927 562.132543   1.088e+07     32.967
```


```
Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz

  operator   time (s)  rel. time        op/s     cyc/op
──────────────────────────────────────────────────────────
     isnan   0.000275   1.000000   3.631e+09      0.111
 nearbyint   0.000288   1.044634   3.475e+09      0.115
      mult   0.000383   1.391573   2.609e+09      0.154
     'max'   0.000386   1.402827   2.588e+09      0.155
     minus   0.000387   1.403742   2.586e+09      0.154
      plus   0.000396   1.437180   2.526e+09      0.162
      ceil   0.000411   1.490724   2.435e+09      0.163
  copysign   0.000432   1.566824   2.317e+09      0.173
  isnormal   0.000462   1.676548   2.166e+09      0.183
       div   0.000475   1.725989   2.103e+09      0.191
     floor   0.000484   1.757510   2.066e+09      0.194
     isinf   0.000508   1.846082   1.967e+09      0.196
      sqrt   0.001425   5.174460   7.016e+08      0.571
     round   0.002613   9.486650   3.827e+08      1.047
      powf   0.003108  11.282463   3.218e+08      1.257
      atan   0.003809  13.829610   2.625e+08      1.526
       log   0.004814  17.479168   2.077e+08      1.916
       exp   0.006186  22.458165   1.617e+08      2.475
      asin   0.007825  28.409675   1.278e+08      3.191
      sinh   0.007898  28.674003   1.266e+08      3.150
       pow   0.008177  29.688547   1.223e+08      3.245
     log10   0.008186  29.718808   1.222e+08      3.276
      cbrt   0.014416  52.337495   6.937e+07      5.812
       sin   0.042037 152.618081   2.379e+07     16.946
       tan   0.046076 167.283007   2.170e+07     18.511
        j0   0.109985 399.311192   9.092e+06     44.171
        j1   0.114187 414.564443   8.758e+06     45.819
```

## See also:
* [Lincoln Atkinson's](https://latkin.org/blog/2014/11/09/a-simple-benchmark-of-various-math-operations/) code/results (C++).
 * [Akseli Palén's](https://github.com/axelpale/js-math-ops-speed) code (JS) and his [comparison](https://www.akselipalen.com/2021/01/13/benchmark-of-elementary-mathematical-operations-in-node-js/) between these tests.
