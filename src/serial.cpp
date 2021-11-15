#include <chrono>
#include <iostream>
#include <map>
#include <vector>

std::vector<std::vector<int>> result;

void PrettyPrint(std::vector<int>& nums) {
  std::cout << "[ ";
  for (auto n : nums) {
    std::cout << n + 1 << " ";
  }
  std::cout << "]" << std::endl;
}

void SetQueen(std::vector<int>& queens, int row, int col) {
  int size = queens.size();

  for (int i = 0; i < row; i++) {
    // vertical attacks
    if (queens[i] == col) {
      return;
    }
    // diagonal attacks
    if (abs(queens[i] - col) == (row - i)) {
      return;
    }
  }

  // column is ok, set the queen
  queens[row] = col;

  if (row == size - 1) {
    result.push_back(queens);
  } else {
    // try to fill next row
    for (int i = 0; i < size; i++) {
      SetQueen(queens, row + 1, i);
    }
  }
}

std::vector<std::vector<int>> Solve(int size) {
  for (int i = 0; i < size; i++) {
    // create separate array for each recursion
    std::vector<int> queens(size, 0);
    // try all positions in first row
    SetQueen(queens, 0, i);
  }

  return result;
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cout << "Please follow template." << std::endl;
    std::cout << "./serial.out -problemType [all, find] -N <queens>"
              << std::endl;

    return EXIT_FAILURE;
  }

  const std::string kProblemType = argv[2];
  const int kQueens = std::atoi(argv[4]);

  auto start = std::chrono::steady_clock::now();
  std::vector<std::vector<int>> v_solutions = Solve(kQueens);
  auto end = std::chrono::steady_clock::now();

  if (v_solutions.empty()) {
    std::cout << "No solutions were found." << std::endl;
  } else {
    if (kProblemType == "find") {
      PrettyPrint(v_solutions[0]);
    } else {
      for (auto solution : v_solutions) {
        PrettyPrint(solution);
      }
    }
  }

  auto diff = end - start;

  std::cout << std::endl;
  std::cout << "Elapsed time: "
            << std::chrono::duration<double, std::milli>(diff).count()
            << " milliseconds." << std::endl;

  return EXIT_SUCCESS;
}
