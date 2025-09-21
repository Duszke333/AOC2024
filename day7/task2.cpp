#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using ull = unsigned long long;

bool explore(ull curr, std::vector<ull>::iterator it, const std::vector<ull>::iterator end, const ull target) {
    if (curr > target) {
        return false;
    }

    if (it == end) { [[unlikely]]
        return curr == target;
    }

    return explore(curr * (*it), it + 1, end, target) ||
    explore(curr + (*it), it + 1, end, target) ||
    explore(curr * std::pow(10, std::to_string(*it).size()) + (*it), it + 1, end, target);
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
  std::string line;
  ull total = 0;
  while(std::getline(input, line)) {
    ull delim_idx = line.find(':');
    ull target = std::stoull(line.substr(0, delim_idx));
    ull num; std::vector<ull> elems;
    std::istringstream iss(line.substr(delim_idx+1));

    while(iss >> num) {
        elems.push_back(num);
    }

    if (explore(elems.at(0), elems.begin() + 1, elems.end(), target)) total += target;
  }

  std::cout << total << std::endl;

  return 0;
}