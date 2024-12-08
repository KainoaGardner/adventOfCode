#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iostream>

struct Input {
  std::vector<long int> result;
  std::vector<std::vector<int>> equation;
};

Input openInput(char *filename) {
  Input input;
  std::ifstream f(filename);

  if (!f.is_open()) {
    std::cout << "Cant open file\n";
    std::abort();
  }

  std::string line;

  while (std::getline(f, line)) {
    std::vector<int> result;

    int resIndex = line.find(':');
    input.result.push_back(stol(line.substr(0, resIndex)));

    std::stringstream ss(line.substr(resIndex + 2));
    std::string item;

    while (getline(ss, item, ' ')) {
      result.push_back(stoi(item));
    }
    input.equation.push_back(result);
  }

  while (std::getline(f, line)) {
  }

  return input;
};

int backtrack(int index, long long total, long long result,
              std::vector<int> input) {
  if (total == result) {
    return result;
  }
  if (index >= input.size() || total > result) {
    return 0;
  }

  long add = backtrack(index + 1, total + input[index], result, input);
  long mult = backtrack(index + 1, total * input[index], result, input);

  if (add != 0 || mult != 0) {
    return result;
  }
  return 0;
}

int part1(Input input) {
  int sum = 0;

  for (int i = 0; i < input.result.size(); i++) {
    std::cout << i << "\n";
    long long result = input.result[i];
    long long total = input.equation[i][0];
    int index = 1;

    sum += backtrack(index, total, result, input.equation[i]);
  }

  return sum;
}

int part2(std::vector<std::array<int, 2>> input) {
  int sum = 0;

  return sum;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Must add filename\n";
    return 0;
  }

  Input input;
  input = openInput(argv[1]);

  std::cout << part1(input) << "\n";
  // std::cout << part2(mulList) << "\n";

  return 0;
}
