# Parallelizing N-Queens

Integrantes:
- Sharon Chullunquía Rosas
- Jerson Zúñiga Coayla

## Requirements
- [OpenMP](https://www.openmp.org/)

## Compile
```sh
g++ -std=c++17 -fopenmp parallel.cpp -o parallel.out
```

## Run
```sh
./parallel.out -problemType [all, find] -N <queens>
```
