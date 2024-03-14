
#include <iostream>

static bool DEBUG = false;

bool has(int *buffer, const int size, int index) {
  bool result = false;
  for (int i = 0; i < size; i++) {
    if (buffer[i] == index) {
      result = true;
      break;
    }
  }
  return result;
}

void PrintMaze(const int sx, const int sy, const int tx, const int ty,
               const unsigned char *map, const int width, const int height,
               int *buffer, const int buffer_size, int path_len) {

  // Print the maze.
  for (int y = -1; y < height + 1; y++) {
    for (int x = -1; x < width + 1; x++) {
      bool isXOutside = x < 0 || x >= width;
      bool isYOutside = y < 0 || y >= height;
      bool isWall = map[y * width + x] == 0;
      bool hasNoPath = path_len <= 0;
      if (isXOutside || isYOutside) {
        // The current cell is an outer wall.
        std::cout << "░";
        continue;
      } else if (isWall) {
        // The current cell is an inner wall.
        std::cout << "▒";
        continue;
      }
      // The current cell is not a wall.
      if (x == tx && y == ty) {
        // The current cell is the end node.
        std::cout << "◎";
        continue;
      } else if (x == sx && y == sy) {
        // The current cell is the start node.
        std::cout << "✗";
        continue;
      } else if (hasNoPath) {
        std::cout << "?";
        continue;
      } else if (has(buffer, path_len, y * width + x)) {
        // The current cell is part of the path.
        std::cout << "●";
        continue;
      } else {
        // The current cell is outside the path.
        std::cout << "○";
        continue;
      }
    }
    std::cout << std::endl;
  }

  // Print costs.
  std::cout << "cost: " << path_len << ". ";

  // Print path (indexes).
  std::cout << "path (index): ";
  for (int i = 0; i < path_len; i++) {
    std::cout << "" << buffer[i];
    if (i < path_len - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "." << std::endl;

  // Print path (coordinates).
  if (DEBUG) {
    std::cout << "path (coord):";
    for (int i = 0; i < path_len; i++) {
      std::cout << " (" << buffer[i] % width << ", " << buffer[i] / width
                << ")";
    }
    std::cout << "." << std::endl;
  }
}
