#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>

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

std::pair<int, int> getGuardPos(std::vector<std::string> input) {
  for (int r = 0; r < input.size(); r++) {
    for (int c = 0; c < input[0].size(); c++) {
      if (input[r][c] == '^') {
        return {r, c};
      }
    }
  }
  return {-1, -1};
}

int getUniqueSpots(std::vector<std::string> input) {
  int sum = 0;

  for (int r = 0; r < input.size(); r++) {
    for (int c = 0; c < input[0].size(); c++) {
      if (input[r][c] == 'X') {
        sum++;
      }
    }
  }

  return sum;
}

int part1(std::vector<std::string> input) {
  std::pair<int, int> pos = getGuardPos(input);
  int m = input.size();
  int n = input[0].size();

  // direct 0 = up 1 = right 2 = down 3 = left
  int direction = 0;
  while (pos.first >= 0 && pos.first < m && pos.second >= 0 && pos.second < n) {

    input[pos.first][pos.second] = 'X';
    switch (direction) {
    case 0:
      if (pos.first - 1 >= 0 && input[pos.first - 1][pos.second] == '#') {
        direction = 1;
      } else {
        pos.first--;
      }
      break;
    case 1:
      if (pos.second + 1 < n && input[pos.first][pos.second + 1] == '#') {
        direction = 2;
      } else {
        pos.second++;
      }
      break;
    case 2:
      if (pos.first + 1 < m && input[pos.first + 1][pos.second] == '#') {
        direction = 3;
      } else {
        pos.first++;
      }
      break;
    case 3:
      if (pos.second - 1 >= 0 && input[pos.first][pos.second - 1] == '#') {
        direction = 0;
      } else {
        pos.second--;
      }
      break;
    }
  };

  return getUniqueSpots(input);
}

int part2(std::vector<std::string> input) {
  std::pair<int, int> startPos = getGuardPos(input);

  int sum = 0;
  int m = input.size();
  int n = input[0].size();

  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      if (input[r][c] == '#' || (r == startPos.first && c == startPos.second)) {
        continue;
      }

      input[r][c] = 'O';
      std::pair<int, int> pos = {startPos.first, startPos.second};
      int direction = 0;
      int count = 0;

      while (pos.first >= 0 && pos.first < m && pos.second >= 0 &&
             pos.second < n && count < m * n) {
        input[pos.first][pos.second] = 'X';

        count++;

        switch (direction) {
        case 0:
          if (pos.first - 1 >= 0 && (input[pos.first - 1][pos.second] == '#' ||
                                     input[pos.first - 1][pos.second] == 'O')) {
            direction = 1;
          } else {
            pos.first--;
          }
          break;
        case 1:
          if (pos.second + 1 < n && (input[pos.first][pos.second + 1] == '#' ||
                                     input[pos.first][pos.second + 1] == 'O')) {
            direction = 2;
          } else {
            pos.second++;
          }
          break;
        case 2:
          if (pos.first + 1 < m && (input[pos.first + 1][pos.second] == '#' ||
                                    input[pos.first + 1][pos.second] == 'O')) {
            direction = 3;
          } else {
            pos.first++;
          }
          break;
        case 3:
          if (pos.second - 1 >= 0 && input[pos.first][pos.second - 1] == '#' ||
              (input[pos.first][pos.second - 1] == 'O')) {
            direction = 0;
          } else {
            pos.second--;
          }
          break;
        }
      }

      if (count >= m * n) {
        sum++;
      }

      input[r][c] = '.';
    }
  }

  return sum;
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
