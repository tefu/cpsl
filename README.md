# CS5300

This project is an implementation of CPSL, a compiler being built for CS5300 at
Utah State University.

# Building the compiler
This project uses:

* [CMake](https://cmake.org/) as a build tool.
* [Flex](http://flex.sourceforge.net/) to generate the CPSL lexical analyzer.

Once you have the above installed, you can run
```
mkdir build
cd build
cmake ..
make
./cpsl
```
to run the compiler. I've tested this build process on Ubuntu with GCC 4.8 and
Arch Linux with GCC 5.3.
