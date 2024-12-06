#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

const std::array<std::pair<int, int>, 4> directions = {
    std::make_pair(0, -1), std::make_pair(1, 0), std::make_pair(0, 1),
    std::make_pair(-1, 0)};

bool cycle(const std::vector<std::string> &map,
           const std::set<std::tuple<int, int, int>> &taken, int row, int col,
           int dir_idx) {
  std::set<std::tuple<int, int, int>> steps = taken;
  while (true) {
    if (row <= 0 || row >= map.size() - 1 || col <= 0 ||
        col >= map[row].size() - 1) {
      return false; // exits map without cycle
    }
    if (steps.count({row, col, dir_idx}) != 0) {
      return true; // cycle
    }
    steps.insert({row, col, dir_idx}); // add step to history

    int next_col = col + directions[dir_idx].first;
    int next_row = row + directions[dir_idx].second;
    if (map[next_row][next_col] == '#') {
      dir_idx = (dir_idx + 1) % 4;
    } else {
      row = next_row;
      col = next_col;
    }
  }
}

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
  lines[row][col] = 'X';
  // to prevent from repeating steps when looking for cycles
  std::set<std::tuple<int, int, int>> taken_steps;
  // do a full run first
  while (row > 0 && row < lines.size() - 1 && col > 0 &&
         col < line.size() - 1) {
    int next_col = col + directions[dir_idx].first;
    int next_row = row + directions[dir_idx].second;
    if (lines[next_row][next_col] == '#') {
      dir_idx = (dir_idx + 1) % 4;
    } else {
      if (lines[next_row][next_col] != 'X') {
        auto map = lines;
        map[next_row][next_col] = '#';
        if (cycle(map, taken_steps, row, col, dir_idx)) {
          total++;
        }
      }
      taken_steps.insert({row, col, dir_idx});
      row = next_row;
      col = next_col;
      lines[row][col] = 'X';
    }
  }
  std::cout << total << std::endl;

  return 0;
}