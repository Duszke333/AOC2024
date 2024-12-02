#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
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
  std::vector<int> left, right;
  int l, r;
  std::string line;
  while (std::getline(input, line)) {
    std::istringstream ss(line);
    if (ss >> l >> r) {
      left.push_back(l);
      right.push_back(r);
    } else {
      std::cerr << "Incorrect line in file!" << std::endl;
      return 0;
    }
  }

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  unsigned long long total = 0;
  for (unsigned long long idx = 0; idx < left.size(); idx++) {
    total += std::abs(left.at(idx) - right.at(idx));
  }

  std::cout << total << std::endl;

  return 0;
}