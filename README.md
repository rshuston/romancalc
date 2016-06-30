# romancalc

A simple roman numeral calculator, written in C and suitable for nearly any command-line environment.
All you need is a reasonably decent C compiler (GCC, CLang, etc.) and GNU make.

The project uses the check framework (https://github.com/libcheck/check) for unit-testing. It's available for nearly any *NIX platform.

To build the executable, run `make`. To build all the tests, run `make alltests`. To run all the tests, run `make runalltests`
or `make --silent runalltests`.

Some examples:

$ ./romancalc.exe 1984  
1984 => MCMLXXXIV

$ ./romancalc.exe MCMLXXXIV  
MCMLXXXIV => 1984

$ ./romancalc.exe MCMLXXXIV + IX  
MCMLXXXIV + IX = MCMXCIII

$ /romancalc.exe MCMXCIII  
MCMXCIII => 1993

$ ./romancalc.exe MCMXCIII - IX  
MCMXCIII - IX = MCMLXXXIV
