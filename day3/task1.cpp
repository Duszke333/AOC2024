#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
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
  std::string line;
  std::regex pattern("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
  while (std::getline(input, line)) {
    for (auto it = std::sregex_iterator(line.begin(), line.end(), pattern);
         it != std::sregex_iterator(); it++) {
      std::smatch found = *it;
      total += std::stoi(found[1].str()) * std::stoi(found[2].str());
    }
  }

  std::cout << total << std::endl;

  return 0;
}