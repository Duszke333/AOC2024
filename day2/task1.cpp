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
  int total = 0;
  int prev, curr;
  int diff;
  bool asc;
  std::string line;
  while (std::getline(input, line)) {
    std::istringstream ss(line);
    ss >> prev >> curr;
    asc = curr > prev ? true : false;
    do {
      diff = prev - curr;
      if ((curr > prev) != asc || diff == 0 || std::abs(diff) > 3) {
        total--;
        break;
      }
      prev = curr;
    } while (ss >> curr);
    total++;
  }

  std::cout << total << std::endl;

  return 0;
}