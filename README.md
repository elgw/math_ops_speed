# Tests the speed of common mathematical operations

## Notes
 * For some operators/functions the speed changes with the
   values of the inputs. Change the code to match whatever
   range that is of interest for you. 

 * There might be more clever ways to time the commands.

## Results

When the arrays with numbers does not fit into the L3-cache, 
many of the operators seems to be limited by memory:


```
$ ./ops 1000000

  operator   time (s)  rel. time          ops/s
───────────────────────────────────────────────
      plus   0.016919   1.499639   5.910609e+08
     minus   0.016278   1.442881   6.143111e+08
       div   0.019361   1.716140   5.164950e+08
      mult   0.016238   1.439268   6.158530e+08
      sqrt   0.053483   4.740605   1.869757e+08
      cbrt   0.204829  18.155582   4.882122e+07
       sin   0.089504   7.933425   1.117270e+08
      asin   0.089054   7.893555   1.122913e+08
      sinh   0.174671  15.482450   5.725048e+07
       log   0.052733   4.674096   1.896362e+08
     log10   0.098759   8.753778   1.012566e+08
  copysign   0.015998   1.418071   6.250587e+08
       pow   0.176686  15.661088   5.659745e+07
       exp   0.059446   5.269120   1.682212e+08
       tan   0.205013  18.171925   4.877731e+07
      atan   0.205515  18.216390   4.865825e+07
     round   0.061776   5.475707   1.618746e+08
 nearbyint   0.018518   1.641374   5.400218e+08
  isnormal   0.011435   1.013572   8.745091e+08
     isnan   0.011282   1.000000   8.863777e+08
      ceil   0.015977   1.416209   6.258807e+08
     floor   0.016097   1.426815   6.212282e+08
```

With less memory (2.5 MB fits into L3) there is better resolution among the fast operators, i.e., `div` is clearly
slower than `plus`, `minus` and `mult`.

```
$ ./ops 100000

  operator   time (s)  rel. time          ops/s
───────────────────────────────────────────────
      plus   0.000799   1.834171   1.252215e+09
     minus   0.000577   1.325988   1.732124e+09
       div   0.001811   4.160044   5.521037e+08
      mult   0.000627   1.438969   1.596126e+09
      sqrt   0.005164  11.859401   1.936671e+08
      cbrt   0.020671  47.477192   4.837640e+07
       sin   0.008996  20.661425   1.111625e+08
      asin   0.008742  20.078421   1.143902e+08
      sinh   0.017772  40.817422   5.626949e+07
       log   0.005450  12.518343   1.834728e+08
     log10   0.010485  24.081733   9.537418e+07
  copysign   0.000698   1.603544   1.432312e+09
       pow   0.018202  41.805587   5.493944e+07
       exp   0.006261  14.380194   1.597180e+08
       tan   0.021825  50.127829   4.581837e+07
      atan   0.020902  48.008204   4.784131e+07
     round   0.006051  13.898218   1.652568e+08
 nearbyint   0.001817   4.174125   5.502411e+08
  isnormal   0.000610   1.400484   1.639987e+09
     isnan   0.000435   1.000000   2.296776e+09
      ceil   0.001583   3.635743   6.317211e+08
     floor   0.001641   3.770090   6.092097e+08
```

System used:
```
$ lscpu
Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
Address sizes:       39 bits physical, 48 bits virtual
CPU(s):              4
On-line CPU(s) list: 0-3
Thread(s) per core:  1
Core(s) per socket:  4
Socket(s):           1
NUMA node(s):        1
Vendor ID:           GenuineIntel
CPU family:          6
Model:               60
Model name:          Intel(R) Core(TM) i5-4690K CPU @ 3.50GHz
Stepping:            3
CPU MHz:             1088.962
CPU max MHz:         3900,0000
CPU min MHz:         800,0000
BogoMIPS:            7000.57
Virtualization:      VT-x
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            6144K
NUMA node0 CPU(s):   0-3
Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm cpuid_fault invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid xsaveopt dtherm ida arat pln pts md_clear flush_l1d
```

```
$ gcc --version
gcc (Ubuntu 8.3.0-6ubuntu1) 8.3.0
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
