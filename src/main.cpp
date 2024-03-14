
#include "findpath.cpp"
#include "printmaze.cpp"

int main(int argc, char *argv[]) {

  static unsigned char map[] = {
      // clang-format off
    1,1,1,1,
    0,1,0,1,
    0,1,1,1,
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 1;
  int ty = 2;
  int width = 4;
  int height = 3;
  int buffer_size = 10;
  int path[buffer_size];

  int cost = FindPath(sx, sy, tx, ty, map, width, height, path, buffer_size);
  PrintMaze(sx, sy, tx, ty, map, width, height, path, buffer_size, cost);

  return 0;
}
