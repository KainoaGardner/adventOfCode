#include <bits/stdc++.h>
#include <cmath>
#include <ctype.h>
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

std::vector<std::array<int, 2>> getValidMult(std::vector<std::string> input) {
  std::vector<std::array<int, 2>> validMult;

  for (int line = 0; line < input.size(); line++) {
    std::string text;
    std::string num1;
    std::string num2;

    int i = 0;

    while (i < input[line].size() - 4) {
      if (input[line].substr(i, 4) == "mul(") {
        int j = i + 4;

        while (j < input[line].size() && j - (i + 4) < 9) {
          if (input[line][j] == ')') {
            break;
          }
          j++;
        }
        if (j - (i + 4) < 9) {
          std::string num1;
          std::string num2;
          int comma = 0;
          bool valid = true;
          for (int k = i + 4; k < j; k++) {
            if ((!isdigit(input[line][k]) && input[line][k] != ',') ||
                (input[line][k] == ',' && num1.size() == 0)) {
              valid = false;
              break;
            }
            if (input[line][k] == ',') {
              comma++;
            } else {
              if (comma == 0) {
                num1 += input[line][k];

              } else if (comma == 1) {
                num2 += input[line][k];
              } else {
                valid = false;
                break;
              }
            }
          }

          if (valid && comma == 1 && num1.size() > 0 && num1.size() <= 3 &&
              num2.size() > 0 && num2.size() <= 3) {
            validMult.push_back({stoi(num1), stoi(num2)});
            i = j;
          }
        }
      }
      i++;
    }
  }

  return validMult;
}

std::vector<std::array<int, 2>>
getValidMultDoDont(std::vector<std::string> input) {
  std::vector<std::array<int, 2>> validMult;
  bool enabled = true;

  for (int line = 0; line < input.size(); line++) {
    std::string text;
    std::string num1;
    std::string num2;

    int i = 0;

    while (i < input[line].size() - 4) {
      if (input[line].substr(i, 4) == "do()") {
        enabled = true;
      }
      if ((i + 7 < input[line].size()) &&
          input[line].substr(i, 7) == "don't()") {
        enabled = false;
      }

      if (input[line].substr(i, 4) == "mul(" && enabled) {
        int j = i + 4;

        while (j < input[line].size() && j - (i + 4) < 9) {
          if (input[line][j] == ')') {
            break;
          }
          j++;
        }
        if (j - (i + 4) < 9) {
          std::string num1;
          std::string num2;
          int comma = 0;
          bool valid = true;
          for (int k = i + 4; k < j; k++) {
            if ((!isdigit(input[line][k]) && input[line][k] != ',') ||
                (input[line][k] == ',' && num1.size() == 0)) {
              valid = false;
              break;
            }
            if (input[line][k] == ',') {
              comma++;
            } else {
              if (comma == 0) {
                num1 += input[line][k];

              } else if (comma == 1) {
                num2 += input[line][k];
              } else {
                valid = false;
                break;
              }
            }
          }

          if (valid && comma == 1 && num1.size() > 0 && num1.size() <= 3 &&
              num2.size() > 0 && num2.size() <= 3) {
            validMult.push_back({stoi(num1), stoi(num2)});
            i = j;
          }
        }
      }
      i++;
    }
  }

  return validMult;
}

int part1(std::vector<std::array<int, 2>> input) {
  int sum = 0;

  for (int i = 0; i < input.size(); i++) {
    sum += input[i][0] * input[i][1];
  }

  return sum;
}

int part2(std::vector<std::array<int, 2>> input) {
  int sum = 0;

  for (int i = 0; i < input.size(); i++) {
    sum += input[i][0] * input[i][1];
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

  std::vector<std::array<int, 2>> mulList;
  // mulList = getValidMult(input);
  mulList = getValidMultDoDont(input);

  // std::cout << part1(mulList) << "\n";
  std::cout << part2(mulList) << "\n";

  return 0;
}
