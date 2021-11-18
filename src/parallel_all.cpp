#include <omp.h>
#include <sys/time.h>
#include <time.h>

#include <iostream>
#include <sstream>

// Number of solutions found
int numofSol = 0;

std::ostringstream globalOss;

int N;

void placeQ(int queens[], int row, int column) {
  for (int i = 0; i < row; i++) {
    // Vertical
    if (queens[i] == column) {
      return;
    }

    // Two queens in the same diagonal
    if (abs(queens[i] - column) == (row - i)) {
      return;
    }
  }

  // Set the queen
  queens[row] = column;

  if (row == N - 1) {
#pragma omp atomic
    numofSol++;

    std::ostringstream oss;
    for (int row = 0; row < N; row++) {
      for (int column = 0; column < N; column++) {
        if (queens[row] == column) {
          oss << column + 1 << " ";
        }
      }
    }
    oss << std::endl;
#pragma omp critical
    globalOss << oss.str();
  }

  else {
    // Increment row
    for (int i = 0; i < N; i++) {
      placeQ(queens, row + 1, i);
    }
  }
}

void solve() {
#pragma omp parallel  // num_threads (30)
#pragma omp single
  {
    for (int i = 0; i < N; i++) {
// New task added for first row and each column recursion.
#pragma omp task
      {
        int arr[N];
        placeQ(arr, 0, i);
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

  N = std::atoi(argv[1]);
  solve();

  std::cout << "#Solutions for " << N << " queens." << std::endl;
  std::cout << numofSol << std::endl;

  std::cout << globalOss.str();
  return 0;
}
