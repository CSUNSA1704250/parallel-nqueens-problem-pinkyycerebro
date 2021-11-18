#include <omp.h>

#include <iostream>
#include <sstream>

int num_solutions = 0;

std::ostringstream buffer;

int size;

void SetQueen(int queens[], int row, int column) {
  for (int i = 0; i < row; i++) {
    // vertical attacks
    if (queens[i] == column) {
      return;
    }
    // diagonal attacks
    if (abs(queens[i] - column) == (row - i)) {
      return;
    }
  }
  // column is ok, set the queen
  queens[row] = column;

  if (row == size - 1) {
#pragma omp atomic
    num_solutions++;

    std::ostringstream oss;

    for (int row = 0; row < size; row++) {
      for (int column = 0; column < size; column++) {
        if (queens[row] == column) {
          oss << column + 1 << " ";
        }
      }
    }
    oss << std::endl;
#pragma omp critical
    buffer << oss.str();
  }

  else {
    // Increment row
    for (int i = 0; i < size; i++) {
      SetQueen(queens, row + 1, i);
    }
  }
}

void Solve() {
#pragma omp parallel
#pragma omp single
  {
    for (int i = 0; i < size; i++) {
#pragma omp task
      {
        int arr[size];
        SetQueen(arr, 0, i);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Please follow template." << std::endl;
    std::cout << "./parallel.out <queens>" << std::endl;
    return EXIT_FAILURE;
  }

  size = std::atoi(argv[1]);
  Solve();

  std::cout << "#Solutions for " << size << " queens." << std::endl;
  std::cout << num_solutions << std::endl;

  std::cout << buffer.str();
  return 0;
}
