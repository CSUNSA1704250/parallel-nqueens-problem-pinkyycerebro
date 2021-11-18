[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6148789&assignment_repo_type=AssignmentRepo)

# Parallelizing N-Queens

Integrantes:
- Sharon Rossely Alisson Chullunquía Rosas
- Jerson Zúñiga Coayla

## Requirements
- [OpenMP](https://www.openmp.org/)

## Project tree
```sh
.
├── bin
│   ├── parallel_all.out
│   ├── parallel.out
│   └── serial.out
├── img
│   └── graph.png
├── Makefile
├── out
│   ├── parallel_all.txt
│   └── parallel.txt
├── README.md
├── src
│   ├── parallel_all.cpp
│   ├── parallel.cpp
│   ├── serial.cpp
│   └── utils.cpp
└── test.sh
```

## Compile
```sh
cd src/
g++ -std=c++17 -O2 -fopenmp parallel_all.cpp -o parallel_all.out
```

## Examples
- Printing all solutions
```sh
time ./parallel_all.out <queens> > solutions.txt
```
- Find a solution and generate board.
```sh
time ./parallel.out -problemType find -N <queens> &&
dot -Tpng graph.dot -o graph.png
```

## Performance test
```sh
./test.sh -problemType [all, find] -N <queens>
```

## Results
```sh
~PD/Practices/parallel-nqueens-problem-pinkyycerebro develop
❯ ./test.sh -problemType all -N 15

> Compile source code.
g++ -std=c++17 -O2 -fopenmp -o bin/serial.out src/serial.cpp
g++ -std=c++17 -O2 -fopenmp -o bin/parallel.out src/parallel.cpp
g++ -std=c++17 -O2 -fopenmp -o bin/parallel_all.out src/parallel_all.cpp

> Calculate.
With parallel            0m34.137s
With parallel (v2.0)     0m22.497s
```

