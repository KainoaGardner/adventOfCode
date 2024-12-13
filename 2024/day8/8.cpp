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

std::unordered_map<char, std::vector<std::pair<int, int>>>
getAntenna(std::vector<std::string> input) {
  std::unordered_map<char, std::vector<std::pair<int, int>>> map;

  for (int r = 0; r < input.size(); r++) {
    for (int c = 0; c < input[0].size(); c++) {
      if (input[r][c] == '.') {
        continue;
      }
      map[input[r][c]].push_back({r, c});
    }
  }

  return map;
}

int part1(std::vector<std::string> input,
          std::unordered_map<char, std::vector<std::pair<int, int>>> map) {
  int sum = 0;
  int m = input.size();
  int n = input[0].size();

  for (auto x : map) {
    for (int i = 0; i < x.second.size(); i++) {
      for (int j = i + 1; j < x.second.size(); j++) {
        int firstr = x.second[i].first;
        int firstc = x.second[i].second;
        int secondr = x.second[j].first;
        int secondc = x.second[j].second;

        int vertDist = secondr - firstr;
        int horiDist = secondc - firstc;

        if (secondr + vertDist < m && secondc + horiDist < n &&
            secondr + vertDist >= 0 && secondc + horiDist >= 0) {
          input[secondr + vertDist][secondc + horiDist] = '#';
        }
        if (firstr - vertDist >= 0 && firstc - horiDist >= 0 &&
            firstr - vertDist < m && firstc - horiDist < n) {
          input[firstr - vertDist][firstc - horiDist] = '#';
        }
      }
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (input[i][j] == '#') {
        sum++;
      }
    }
  }

  return sum;
}

int part2(std::vector<std::string> input,
          std::unordered_map<char, std::vector<std::pair<int, int>>> map) {
  int sum = 0;
  int m = input.size();
  int n = input[0].size();

  for (auto x : map) {
    for (int i = 0; i < x.second.size(); i++) {
      for (int j = i + 1; j < x.second.size(); j++) {
        int vertDist = x.second[j].first - x.second[i].first;
        int horiDist = x.second[j].second - x.second[i].second;

        int currr = x.second[i].first;
        int currc = x.second[i].second;

        while (currr >= 0 && currr < m && currc >= 0 && currc < n) {
          input[currr][currc] = '#';
          currr += vertDist;
          currc += horiDist;
        }

        currr = x.second[i].first;
        currc = x.second[i].second;

        while (currr >= 0 && currr < m && currc >= 0 && currc < n) {
          input[currr][currc] = '#';
          currr -= vertDist;
          currc -= horiDist;
        }
      }
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (input[i][j] == '#') {
        sum++;
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

  std::vector<std::string> input = openInput(argv[1]);
  std::unordered_map<char, std::vector<std::pair<int, int>>> map =
      getAntenna(input);

  // std::cout << part1(input, map) << "\n";
  std::cout << part2(input, map) << "\n";

  return 0;
}
