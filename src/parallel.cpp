#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

#include "utils.cpp"

std::stringstream buffer;
int num_solutions = 0;

std::string kProblemType;

void SetQueen(int* queens, int size, int row, int col) {
  if (num_solutions > 0 && kProblemType == "find") {
    return;
  }

  for (int i = 0; i < row; i++) {
    // vertical attacks
    if (*(queens + i) == col) {
      return;
    }
    // diagonal attacks
    if (abs(*(queens + i) - col) == (row - i)) {
      return;
    }
  }

  // column is ok, set the queen
  *(queens + row) = col;

  if (row == size - 1) {
    #pragma omp atomic
    num_solutions++;

    std::ostringstream oss;

    for (int i = 0; i < size; i++) {
      oss << *(queens + i) + 1 << " ";
    }
    oss << std::endl;

    #pragma omp critical
    buffer << oss.str();

    if (kProblemType == "find") {
      return;
    }
  } else {
    // try to fill next row
    for (int i = 0; i < size; i++) {
      SetQueen(queens, size, row + 1, i);
    }
  }
}

void Solve(int size) {
  #pragma omp parallel for
  for (int i = 0; i < size; i++) {
    SetQueen(new int[size], size, 0, i);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cout << "Please follow template." << std::endl;
    std::cout << "./parallel.out -problemType [all, find] -N <queens>"
              << std::endl;

    return EXIT_FAILURE;
  }

  kProblemType = argv[2];
  const int kQueens = std::atoi(argv[4]);

  auto start = std::chrono::steady_clock::now();
  Solve(kQueens);
  auto end = std::chrono::steady_clock::now();

  std::cout << "#Solutions for " << kQueens << " queens." << std::endl;
  std::cout << num_solutions << std::endl;
  std::cout << buffer.str();

  if (kProblemType == "find") {
    int n;
    int positions[kQueens];
    int i = 0;

    while (buffer >> n) {
      *(positions + i) = n;
      i++;
    }
    generar_tablero(positions, kQueens);
  }

  auto diff = end - start;
  std::cout << std::endl;
  std::cout << "Elapsed time: "
            << std::chrono::duration<double, std::milli>(diff).count()
            << " milliseconds." << std::endl;

  return EXIT_SUCCESS;
}
