#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool is_valid(const std::vector<int> &nums) {
  bool asc = (nums[1] > nums[0]);
  for (size_t i = 1; i < nums.size(); ++i) {
    int diff = std::abs(nums[i] - nums[i - 1]);
    if (diff < 1 || diff > 3 || (nums[i] > nums[i - 1]) != asc) {
      return false;
    }
  }
  return true;
}

bool fixable(const std::vector<int> &nums) {
  for (size_t i = 0; i < nums.size(); ++i) {
    std::vector<int> modified(nums);
    modified.erase(modified.begin() + i);
    if (is_valid(modified)) {
      return true;
    }
  }
  return false;
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
  int num;
  std::string line;
  while (std::getline(input, line)) {
    std::istringstream ss(line);
    std::vector<int> nums;
    while (ss >> num) {
      nums.push_back(num);
    }
    if (is_valid(nums) || fixable(nums)) {
      total++;
    }
  }

  std::cout << total << std::endl;

  return 0;
}