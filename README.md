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
     isnan   0.007266   1.000000   1.376e+09      0.280
     floor   0.007347   1.011098   1.361e+09      0.287
      ceil   0.007353   1.011858   1.360e+09      0.287
     isinf   0.008211   1.130002   1.218e+09      0.324
  isnormal   0.008303   1.142584   1.204e+09      0.329
 nearbyint   0.008305   1.142905   1.204e+09      0.318
       div   0.009471   1.303378   1.056e+09      0.368
      mult   0.009564   1.316162   1.046e+09      0.366
     minus   0.009670   1.330843   1.034e+09      0.368
     'max'   0.009769   1.344345   1.024e+09      0.389
      plus   0.009927   1.366139   1.007e+09      0.372
  copysign   0.010301   1.417648   9.708e+08      0.437
      sqrt   0.014594   2.008451   6.852e+08      0.581
     round   0.055402   7.624411   1.805e+08      2.212
       exp   0.100948  13.892370   9.906e+07      4.049
       sin   0.109773  15.106898   9.110e+07      4.399
      asin   0.133511  18.373710   7.490e+07      5.350
      sinh   0.141346  19.451945   7.075e+07      5.670
      atan   0.162127  22.311713   6.168e+07      6.495
      cbrt   0.163287  22.471413   6.124e+07      6.542
       tan   0.182791  25.155485   5.471e+07      7.330
       log   0.186715  25.695577   5.356e+07      7.499
     log10   0.192381  26.475337   5.198e+07      7.729
       pow   0.448946  61.783457   2.227e+07     18.007
```

## See also:
* [Lincoln Atkinson's](https://latkin.org/blog/2014/11/09/a-simple-benchmark-of-various-math-operations/) code/results (C++).
 * [Akseli Palén's](https://github.com/axelpale/js-math-ops-speed) code (JS) and his [comparison](https://www.akselipalen.com/2021/01/13/benchmark-of-elementary-mathematical-operations-in-node-js/) between these tests.
