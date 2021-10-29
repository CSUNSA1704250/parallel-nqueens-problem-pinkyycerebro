[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6148789&assignment_repo_type=AssignmentRepo)

# Parallelizing N-Queens

Integrantes:
- Sharon Chullunquía Rosas
- Jerson Zúñiga Coayla

## Requirements
- [OpenMP](https://www.openmp.org/)

## Compile
```sh
cd src/
g++ -std=c++17 -fopenmp parallel.cpp -o parallel.out
```

## Run
```sh
./parallel.out -problemType [all, find] -N <queens>
```

## Examples
- Printing all solutions
```sh
time ./parallel.out -problemType all -N 6 > solutions.txt
```
- Find a solution and generate `graph.dot` file.
```sh
time ./parallel.out -problemType find -N 6
```

## Results
Generate chessboard for a solution with `dot` from Graphviz.
```sh
dot -Tpng graph.dot -o graph.png
```
![Chessboard with six queens](./img/graph.png)

