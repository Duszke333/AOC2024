#include <algorithm>
#include <array>
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
  int total = 1;
  int row, col, curr_row = 0;
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(input, line)) {
    lines.push_back(line);
    auto it = std::find_if(line.begin(), line.end(),
                           [](char c) { return c != '.' && c != '#'; });
    if (it != line.end()) {
      row = curr_row;
      col = std::distance(line.begin(), it);
    }
    curr_row++;
  }
  const std::array<std::pair<int, int>, 4> directions = {
      std::make_pair(0, -1), std::make_pair(1, 0), std::make_pair(0, 1),
      std::make_pair(-1, 0)};
  int dir_idx;
  switch (lines[row][col]) {
  case '^':
    dir_idx = 0;
    break;
  case '>':
    dir_idx = 1;
    break;
  case 'v':
    dir_idx = 2;
    break;
  case '<':
    dir_idx = 3;
    break;
  default:
    std::cerr << "ERROR: Unknown direction!" << std::endl;
    return 1;
  }

  int next_col, next_row;
  lines[row][col] = 'X';
  while (row > 0 && row < lines.size() - 1 && col > 0 &&
         col < line.size() - 1) {
    next_col = col + directions[dir_idx].first;
    next_row = row + directions[dir_idx].second;
    switch (lines[next_row][next_col]) {
      break;
    case '#': // turn
      dir_idx = (dir_idx + 1) % 4;
      break;
    case '.': // mark as visited and increase counter
      total++;
      lines[next_row][next_col] = 'X';
    default: // 'X', do nothing
      col = next_col;
      row = next_row;
      break;
    }
  }
  std::cout << total << std::endl;

  return 0;
}