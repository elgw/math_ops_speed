# Tests the speed of common mathematical operations


When the arrays with numbers does not fit into the L3-cache, 
many of the operators seems to be limited by memory:


```
$ ./ops 100000000

  operator   time (s)  rel. time          ops/s
───────────────────────────────────────────────
      plus   1.632992   1.035198   6.123730e+08
     minus   1.619034   1.026350   6.176521e+08
       div   1.902835   1.206260   5.255316e+08
      mult   1.623144   1.028956   6.160883e+08
      sqrt   5.185965   3.287526   1.928281e+08
      cbrt  20.270663  12.850132   4.933238e+07
       sin   8.749371   5.546467   1.142939e+08
      sinh  17.467042  11.072839   5.725068e+07
       log   5.272988   3.342692   1.896458e+08
     log10   9.847130   6.242367   1.015524e+08
  copysign   1.577467   1.000000   6.339276e+08
       pow  17.783324  11.273339   5.623246e+07
       exp   5.973025   3.786465   1.674193e+08
       tan  20.569742  13.039726   4.861510e+07
      tanh  18.053722  11.444751   5.539024e+07
```

With less memory (2.5 MB fits into L3) there is better resolution among the fast operators, i.e., `div` is clearly
slower than `plus`, `minus` and `mult`.

```
$ ./ops 100000

  operator   time (s)  rel. time          ops/s
───────────────────────────────────────────────
      plus   0.000948   1.522132   1.054312e+09
     minus   0.000623   1.000000   1.604802e+09
       div   0.002283   3.664414   4.379423e+08
      mult   0.000674   1.080972   1.484591e+09
      sqrt   0.005629   9.033595   1.776482e+08
      cbrt   0.022549  36.186189   4.434845e+07
       sin   0.009650  15.486197   1.036279e+08
      sinh   0.019276  30.934863   5.187680e+07
       log   0.005434   8.721122   1.840132e+08
     log10   0.010241  16.435208   9.764413e+07
  copysign   0.000687   1.102513   1.455585e+09
       pow   0.018551  29.770791   5.390524e+07
       exp   0.006052   9.711669   1.652447e+08
       tan   0.020877  33.503909   4.789893e+07
      tanh   0.018217  29.234307   5.489446e+07
```
