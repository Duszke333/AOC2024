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
  std::vector<std::string> lines;
  while (std::getline(input, line)) {
    lines.push_back(line);
  }
  bool found;
  int rows = lines.size();
  int cols = lines[0].size();
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (lines[i][j] == 'A') {
        if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
          continue;
        }
        found = true;
        char neighbours[4] = {lines[i - 1][j - 1], lines[i - 1][j + 1],
                              lines[i + 1][j + 1], lines[i + 1][j - 1]};
        for (auto n : neighbours) {
          if (n == 'X' || n == 'A') {
            found = false;
            break;
          }
        }
        if (found && neighbours[0] != neighbours[2] &&
            neighbours[1] != neighbours[3]) {
          total++;
        }
      }
    }
  }

  std::cout << total << std::endl;

  return 0;
}