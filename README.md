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

## See also:
* [Lincoln Atkinson's](https://latkin.org/blog/2014/11/09/a-simple-benchmark-of-various-math-operations/) code/results (C++).
 * [Akseli Palén's](https://github.com/axelpale/js-math-ops-speed) code (JS) and his [comparison](https://www.akselipalen.com/2021/01/13/benchmark-of-elementary-mathematical-operations-in-node-js/) between these tests.

## Results

```
$ ./ops 100000 ; ./ops 1000000

  operator   time (s)  rel. time        op/s     cyc/op
──────────────────────────────────────────────────────────
     isnan   0.000271   1.000000   3.696e+09      0.109
      ceil   0.000394   1.455108   2.540e+09      0.158
     floor   0.000395   1.459303   2.533e+09      0.158
     minus   0.000399   1.473184   2.509e+09      0.149
      mult   0.000400   1.478273   2.500e+09      0.149
      plus   0.000417   1.540535   2.399e+09      0.150
     'max'   0.000421   1.557029   2.374e+09      0.151
  isnormal   0.000449   1.658373   2.229e+09      0.179
 nearbyint   0.000481   1.779361   2.077e+09      0.191
  copysign   0.000498   1.839439   2.009e+09      0.155
       div   0.000501   1.851309   1.996e+09      0.191
     isinf   0.000718   2.652649   1.393e+09      0.286
      sqrt   0.001510   5.578819   6.625e+08      0.582
     round   0.005421  20.035852   1.845e+08      2.173
       exp   0.010057  37.169409   9.943e+07      4.030
       sin   0.010885  40.229376   9.187e+07      4.348
      asin   0.013252  48.977061   7.546e+07      5.317
      sinh   0.014061  51.965578   7.112e+07      5.615
      atan   0.016123  59.587848   6.202e+07      6.456
      cbrt   0.016925  62.549549   5.908e+07      6.502
       tan   0.018378  67.920183   5.441e+07      7.320
       log   0.018592  68.710110   5.379e+07      7.430
     log10   0.019066  70.464181   5.245e+07      7.685
       pow   0.045005 166.327136   2.222e+07     17.994

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

### System used:
```
$ lscpu
Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
CPU(s):              8
On-line CPU(s) list: 0-7
Thread(s) per core:  2
Core(s) per socket:  4
Socket(s):           1
NUMA node(s):        1
Vendor ID:           GenuineIntel
CPU family:          6
Model:               94
Model name:          Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
Stepping:            3
CPU MHz:             800.012
CPU max MHz:         4200.0000
CPU min MHz:         800.0000
BogoMIPS:            8016.00
Virtualization:      VT-x
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            8192K
NUMA node0 CPU(s):   0-7
Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp md_clear flush_l1d
```

```
$ gcc --version
gcc (Ubuntu 9.1.0-2ubuntu2~18.04) 9.1.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
