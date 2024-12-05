#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <vector>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << "filepath" << std::endl;
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Could not open file!" << std::endl;
    return 2;
  }
  int total = 0;
  int left, right;
  std::string line;
  std::unordered_map<int, std::vector<int>> ruleset;
  // first loop - collect ruleset
  while (std::getline(input, line)) {
    if (line == "") {
      break;
    }
    std::replace(line.begin(), line.end(), '|', ' ');
    std::istringstream ss(line);
    if (ss >> left >> right) {
      ruleset[left].push_back(right);
    } else {
      std::cerr << "Incorrect line in file!" << std::endl;
      return 0;
    }
  }
  // second loop - read updates
  bool correct;
  while (std::getline(input, line)) {
    std::vector<int> previous_elements;
    correct = true;
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream ss(line);
    while (ss >> left) {
      const auto &rules = ruleset[left];
      auto pos = previous_elements.end();
      for (auto it = previous_elements.begin(); it != previous_elements.end();
           it++) {
        if (std::find(rules.begin(), rules.end(), *it) != rules.end()) {
          pos = it;
          correct = false;
          break;
        }
      }
      previous_elements.insert(pos, left);
    }
    if (!correct) {
      total += previous_elements.at(previous_elements.size() / 2);
    }
  }

  std::cout << total << std::endl;

  return 0;
}