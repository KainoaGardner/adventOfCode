#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

std::vector<std::vector<int>> openInput(char *filename, char delim) {
  std::ifstream f(filename);

  if (!f.is_open()) {
    std::cout << "Cant open file\n";
    std::abort();
  }

  std::string line;
  std::vector<std::vector<int>> input;

  while (std::getline(f, line)) {
    if (line.find(delim) < line.length()) {
      std::vector<int> result;
      std::stringstream ss(line);
      std::string item;

      while (getline(ss, item, delim)) {
        result.push_back(std::stoi(item));
      }

      input.push_back(result);
    }
  }

  return input;
};

bool checkOrder(std::vector<std::vector<int>> rules, std::vector<int> log) {
  std::unordered_map<int, int> indexMap;

  for (int i = 0; i < log.size(); i++) {
    indexMap[log[i]] = i;
  }

  for (int i = 0; i < rules.size(); i++) {
    int a = rules[i][0];
    int b = rules[i][1];

    if (indexMap.count(a) != 0 && indexMap.count(b) != 0 &&
        indexMap[b] < indexMap[a]) {
      return false;
    }
  }

  return true;
}

int part1(std::vector<std::vector<int>> rules,
          std::vector<std::vector<int>> logs) {

  int sum = 0;
  for (int i = 0; i < logs.size(); i++) {
    if (checkOrder(rules, logs[i])) {
      sum += logs[i][logs[i].size() / 2];
    }
  }

  return sum;
}

void dfs(int node, std::vector<int> stack, std::unordered_set<int> visited,
         std::unordered_map<int, std::vector<int>> adj, std::vector<int> log) {

  // if (visited.find(node) != visited.end() ||
  //     count(log.begin(), log.end(), node) == 0) {
  //   return;
  // }

  std::unordered_set<int>::iterator i;

  for (i = visited.begin(); i != visited.end(); i++) {
    std::cout << *i << " ";
  }
  std::cout << "\n";

  if (visited.count(node) != 0) {
    return;
  }

  visited.insert(node);
  for (int i = 0; i < adj[node].size(); i++) {
    dfs(adj[node][i], stack, visited, adj, log);
  }

  stack.push_back(node);
}

void topSort(std::vector<int> log,
             std::unordered_map<int, std::vector<int>> adj) {
  std::vector<int> stack;
  std::unordered_set<int> visited;

  for (int i = 0; i < log.size(); i++) {
    dfs(log[i], stack, visited, adj, log);
  }

  for (int i = 0; i < log.size(); i++) {
    log[i] = stack[stack.size() - i - 1];
  }
}

int part2(std::vector<std::vector<int>> rules,
          std::vector<std::vector<int>> logs) {

  int sum = 0;

  std::unordered_map<int, std::vector<int>> adj;

  for (int i = 0; i < rules.size(); i++) {
    adj[rules[i][0]].push_back(rules[i][1]);
  }

  for (int i = 0; i < logs.size(); i++) {
    if (checkOrder(rules, logs[i])) {
      continue;
    }
    topSort(logs[i], adj);
    sum += logs[i][logs[i].size() / 2];
  }

  return sum;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Must add filename\n";
    return 0;
  }

  std::vector<std::vector<int>> rules;
  std::vector<std::vector<int>> logs;
  rules = openInput(argv[1], '|');
  logs = openInput(argv[1], ',');

  // std::cout << part1(rules, logs) << "\n";

  // doesnt work
  //  std::cout << part2(rules, logs) << "\n";

  return 0;
}
