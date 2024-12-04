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

  std::vector<std::pair<int, int>> directions = {
      {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

  std::string key = "XMAS";
  int x, y, row, col;
  bool found;
  int rows = lines.size();
  int cols = lines[0].size();
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (lines[i][j] == 'X') {
        for (auto dir : directions) {
          found = true;
          x = dir.first;
          y = dir.second;
          for (int step = 1; step < 4; step++) {
            row = i + step * x;
            col = j + step * y;
            if (row < 0 || row >= rows || col < 0 || col >= cols ||
                lines[row][col] != key[step]) {
              found = false;
              break;
            }
          }
          if (found) {
            total++;
          }
        }
      }
    }
  }

  std::cout << total << std::endl;

  return 0;
}