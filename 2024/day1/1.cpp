#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

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

struct Result {
  std::vector<int> list1;
  std::vector<int> list2;
};

Result getLists(std::vector<std::vector<int>> input) {
  std::vector<int> list1;
  std::vector<int> list2;

  for (int i = 0; i < input.size(); i++) {
    list1.push_back(input[i][0]);
    list2.push_back(input[i][1]);
  }

  Result result;
  result.list1 = list1;
  result.list2 = list2;

  return result;
}

int part1(std::vector<std::vector<int>> input) {
  Result lists = getLists(input);
  sort(lists.list1.begin(), lists.list1.end());
  sort(lists.list2.begin(), lists.list2.end());

  int sum = 0;
  for (int i = 0; i < lists.list1.size(); i++) {
    sum += abs(lists.list1[i] - lists.list2[i]);
  }
  return sum;
}

int part2(std::vector<std::vector<int>> input) {
  Result lists = getLists(input);

  std::unordered_map<int, int> rightCount;

  for (int i = 0; i < lists.list2.size(); i++) {
    rightCount[lists.list2[i]]++;
  }

  int sum = 0;
  for (int i = 0; i < lists.list1.size(); i++) {
    sum += lists.list1[i] * rightCount[lists.list1[i]];
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

  std::cout << part1(input) << "\n";
  std::cout << part2(input) << "\n";

  return 0;
}
