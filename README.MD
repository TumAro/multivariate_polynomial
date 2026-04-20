If you do not have a C++ compiler installed, install with the following command in your linux system.
```
sudo apt install g++ -y
```

**Additional Note:** for constant values I am using the character `@` for variable with exponent of 0.  

Make sure gsl is installed.

## Build
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

## TEST
to test the code, just run the following from your shell:
```bash
cd build
./test_case
./test_gsl
```