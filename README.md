# CS5300

This project is an implementation of CPSL, a compiler being built for CS5300 at
Utah State University.

# Building the compiler
This project uses:

* [CMake](https://cmake.org/) as a build tool.
* [Flex](http://flex.sourceforge.net/) to generate the CPSL lexical analyzer.
* [Bison](https://www.gnu.org/software/bison) to parse the CPSL syntax.

Once you have the above installed, you can run
```
mkdir build
cd build
cmake ..
make
./cpsl
```
to start the compiler. I tested this build process on Ubuntu with GCC 4.8 and
Arch Linux with GCC 5.3.

# Usage
The compiler takes the following arguments on the command line:
```
./cpsl input.cpsl output.asm
```
This will generate `output.asm`, which should be run in a MIPS simulator.


# Language Tests

I added some language tests that run my compiler on the CPSL programs from
[ksundberg/CS6300](https://github.com/ksundberg/CS6300). Same steps as before,
but now we run `make language_test` instead of starting the compiler with
`./cpsl`. The full process for running the language tests would look like:

``` 
mkdir build 
cd build 
cmake .. 
make 
make language_test 
```
# Unit Tests

I also added unit tests for the C++ codebase (rather than the CPSL one). After
getting your CMake build directory setup, try running
```
make unit_tests
./unit_tests

```
to run the unit tests.

# Bison Output

After running `make` in your CMake build directory, the file `bison.output` will
be generated. This contains information about the parser's states (also
warnings, conflicts, useless rules, etc.)
