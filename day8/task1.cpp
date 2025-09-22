#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

struct Pos {
    int x;
    int y;

    Pos(int x_, int y_) : x(x_), y(y_) {}

    bool operator==(const Pos& other) const {
        return x == other.x && y == other.y;
    }

    Pos operator+(const Pos& other) const {
        return Pos(x + other.x, y + other.y);
    }

    Pos operator-(const Pos& other) const {
        return Pos(x - other.x, y - other.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Pos& pos) {
        os << '(' << pos.x << ',' << pos.y << ')';
        return os;
    }
};

namespace std {
    template <>
    struct hash<Pos> {
        std::size_t operator()(const Pos& p) const noexcept {
            return std::hash<unsigned int>()(p.x) ^ (std::hash<unsigned int>()(p.y) << 1);
        }
    };
}

bool inbound(const Pos& pos, int width, int height) {
    return 0 <= pos.x && pos.x < width && 0 <= pos.y && pos.y < height;
}

Pos distance(const Pos& p1, const Pos& p2) {
    return p2 - p1;
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
  int row = 0; int width;
  std::unordered_map<char, std::vector<Pos>> antennas;
  while(std::getline(input, line)) {
    for (int col = 0; col < line.size(); ++col) {
        if (line[col] != '.') { [[unlikely]]
            antennas[line[col]].push_back(Pos(row, col));
        }
    }
    ++row;
    width = line.size();
  }

  std::unordered_set<Pos> antinodes;

  for (const auto& [_, poses] : antennas) {
    for (int i = 0; i < poses.size(); ++i) {
        for (int j = i + 1; j < poses.size(); ++j) {
            const Pos& p1 = poses[i]; const Pos& p2 = poses[j];
            const Pos dst = distance(p1, p2);
            if (inbound(p1 - dst, width, row)) {
                antinodes.insert(p1 - dst);
            }
            if (inbound(p2 + dst, width, row)) {
                antinodes.insert(p2 + dst);
            }
        }
    }
  }

  std::cout << antinodes.size() << std::endl;

  return 0;
}