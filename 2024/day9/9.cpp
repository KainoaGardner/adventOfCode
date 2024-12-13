#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdint.h>

char *openInput(char *filename, int &size) {
  std::ifstream f(filename);

  if (!f.is_open()) {
    std::cout << "Cant open file\n";
    std::abort();
  }

  std::string line;
  std::getline(f, line);

  size = line.size();

  char *result = new char[size];

  strcpy(result, line.c_str());

  return result;
};

std::vector<int> expandInput(char *input, int size) {
  std::vector<int> expanded;

  bool file = true;
  int id = 0;

  for (int i = 0; i < size; i++) {
    int num = input[i] - '0';

    if (file) {
      for (int j = 0; j < num; j++) {
        expanded.push_back(id);
      }
      id++;
      file = false;
    } else {
      for (int j = 0; j < num; j++) {
        expanded.push_back(-1);
      }
      file = true;
    }
  }

  return expanded;
}

uint64_t part1(char *input, int size) {
  uint64_t sum = 0;

  std::vector<int> expanded = expandInput(input, size);

  int i = 0;
  int j = expanded.size() - 1;

  while (expanded[i] != -1) {
    i++;
  }

  while (expanded[j] == -1) {
    j--;
  }

  while (i < j) {

    expanded[i] = expanded[j];
    expanded[j] = -1;

    while (expanded[i] != -1) {
      i++;
    }

    while (expanded[j] == -1) {
      j--;
    }
  }

  for (int k = 0; k < expanded.size(); k++) {
    if (expanded[k] == -1) {
      continue;
    }
    sum += k * expanded[k];
  }

  return sum;
}

uint64_t part2(char *input, int size) {
  uint64_t sum = 0;

  std::vector<int> expanded = expandInput(input, size);

  int i = 0;
  int j = expanded.size() - 1;

  while (expanded[i] != -1) {
    i++;
  }

  while (expanded[j] == -1) {
    j--;
  }

  while (i < j) {

    expanded[i] = expanded[j];
    expanded[j] = -1;

    while (expanded[i] != -1) {
      i++;
    }

    while (expanded[j] == -1) {
      j--;
    }
  }

  for (int k = 0; k < expanded.size(); k++) {
    if (expanded[k] == -1) {
      continue;
    }
    sum += k * expanded[k];
  }

  return sum;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Must add filename\n";
    return 0;
  }

  int size = 0;
  char *input = openInput(argv[1], size);

  std::cout << part1(input, size) << "\n";
  // std::cout << part2(input) << "\n";

  delete[] input;

  return 0;
}
