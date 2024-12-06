#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::vector<int>> openInput(char *filename) {
  std::ifstream f(filename);

  if (!f.is_open()) {
    std::cout << "Cant open file\n";
    std::abort();
  }

  std::string line;
  std::vector<std::vector<int>> input;

  while (std::getline(f, line)) {
    std::stringstream ss(line);
    std::string word;
    std::vector<int> words;

    while (ss >> word) {
      words.push_back(stoi(word));
    }

    input.push_back(words);
  }

  return input;
};

bool checkSafe(std::vector<int> level) {
  bool increase = true;

  if (level[0] > level[1]) {
    increase = false;
  }

  for (int i = 1; i < level.size(); i++) {
    int diff = abs(level[i] - level[i - 1]);
    if (diff < 1 || diff > 3) {
      return false;
    }

    if (increase && level[i] < level[i - 1]) {
      return false;
    } else if (!increase && level[i] > level[i - 1]) {
      return false;
    }
  }

  return true;
}

int part1(std::vector<std::vector<int>> input) {
  int sum = 0;
  for (int i = 0; i < input.size(); i++) {
    if (checkSafe(input[i])) {
      sum++;
    }
  }

  return sum;
}

int part2(std::vector<std::vector<int>> input) {
  int sum = 0;
  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[i].size(); j++) {
      std::vector<int> newVect;
      std::copy(input[i].begin(), input[i].end(), std::back_inserter(newVect));

      newVect.erase(newVect.begin() + j);
      if (checkSafe(newVect)) {
        sum++;
        break;
      }
    }
  }

  return sum;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Must add filename\n";
    return 0;
  }

  std::vector<std::vector<int>> input;
  input = openInput(argv[1]);

  // std::cout << part1(input) << "\n";
  std::cout << part2(input) << "\n";

  return 0;
}
