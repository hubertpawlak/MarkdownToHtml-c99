# How to install all dependencies?
```console
sudo apt install build-essential cmake
```
*may vary depending on chosen distro*

# How to compile?
Generate `Makefile` using
```console
cd build
cmake ..
```
and compile with
```console
cmake --build .
```
(inside `build` directory)

# How to run?
(inside `build` directory)
```console
chmod o+x ./bin/*
./bin/main
```

# How to run unit tests?
(inside `build` directory)
```console
ctest
```

# Notes
This program was compiled on Debian (using WSL).