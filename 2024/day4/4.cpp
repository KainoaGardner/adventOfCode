#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iostream>

std::vector<std::string> openInput(char *filename) {
  std::ifstream f(filename);

  if (!f.is_open()) {
    std::cout << "Cant open file\n";
    std::abort();
  }

  std::string line;
  std::vector<std::string> input;

  while (std::getline(f, line)) {

    input.push_back(line);
  }

  return input;
};

// direct  -1 = left 1 = right
bool checkHorizontal(std::vector<std::string> input, int r, int c, int direct) {
  if (c + (3 * direct) < 0 || c + (3 * direct) >= input[0].size()) {
    return false;
  }

  if (input[r][c] == 'X' && input[r][c + (1 * direct)] == 'M' &&
      input[r][c + (2 * direct)] == 'A' && input[r][c + (3 * direct)] == 'S') {
    return true;
  }
  return false;
}

// direct  -1 = up 1 = down
bool checkVertical(std::vector<std::string> input, int r, int c, int direct) {
  if (r + (3 * direct) < 0 || r + (3 * direct) >= input.size()) {
    return false;
  }

  if (input[r][c] == 'X' && input[r + (1 * direct)][c] == 'M' &&
      input[r + (2 * direct)][c] == 'A' && input[r + (3 * direct)][c] == 'S') {
    return true;
  }
  return false;
}

// rDirect  -1 = up 1 = down   cDirect -1 = left   1 = right
bool checkDiagonal(std::vector<std::string> input, int r, int c, int rDirect,
                   int cDirect) {

  if (r + (3 * rDirect) < 0 || r + (3 * rDirect) >= input.size()) {
    return false;
  }
  if (c + (3 * cDirect) < 0 || c + (3 * cDirect) >= input[0].size()) {
    return false;
  }

  if (input[r][c] == 'X' &&
      input[r + (1 * rDirect)][c + (1 * cDirect)] == 'M' &&
      input[r + (2 * rDirect)][c + (2 * cDirect)] == 'A' &&
      input[r + (3 * rDirect)][c + (3 * cDirect)] == 'S') {
    return true;
  }
  return false;
}

bool checkX_MAS(std::vector<std::string> input, int r, int c) {
  if (r - 1 < 0 || r + 1 >= input.size() || c - 1 < 0 ||
      c + 1 >= input[0].size()) {
    return false;
  }

  if (input[r][c] != 'A') {
    return false;
  }

  if (!(input[r - 1][c - 1] == 'M' && input[r + 1][c + 1] == 'S') &&
      !(input[r - 1][c - 1] == 'S' && input[r + 1][c + 1] == 'M')) {
    return false;
  }

  if (!(input[r + 1][c - 1] == 'M' && input[r - 1][c + 1] == 'S') &&
      !(input[r + 1][c - 1] == 'S' && input[r - 1][c + 1] == 'M')) {
    return false;
  }

  return true;
}

int part1(std::vector<std::string> input) {
  int count = 0;
  for (int r = 0; r < input.size(); r++) {
    for (int c = 0; c < input[0].size(); c++) {
      if (input[r][c] == 'X') {
        if (checkHorizontal(input, r, c, -1)) {
          count++;
        }
        if (checkHorizontal(input, r, c, 1)) {
          count++;
        }

        if (checkVertical(input, r, c, -1)) {
          count++;
        }
        if (checkVertical(input, r, c, 1)) {
          count++;
        }

        if (checkDiagonal(input, r, c, -1, -1)) {
          count++;
        }
        if (checkDiagonal(input, r, c, -1, 1)) {
          count++;
        }

        if (checkDiagonal(input, r, c, 1, -1)) {
          count++;
        }
        if (checkDiagonal(input, r, c, 1, 1)) {
          count++;
        }
      }
    }
  }

  return count;
}

int part2(std::vector<std::string> input) {
  int count = 0;
  for (int r = 0; r < input.size(); r++) {
    for (int c = 0; c < input[0].size(); c++) {
      if (input[r][c] == 'A') {
        if (checkX_MAS(input, r, c)) {
          count++;
        }
      }
    }
  }

  return count;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Must add filename\n";
    return 0;
  }

  std::vector<std::string> input;
  input = openInput(argv[1]);

  // std::cout << part1(input) << "\n";
  std::cout << part2(input) << "\n";

  return 0;
}
