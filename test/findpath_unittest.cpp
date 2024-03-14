
#include "../src/findpath.cpp"
#include "../src/printmaze.cpp"
#include "gtest/gtest.h"
#include <climits>

using namespace std;

//
// NOTES
//
//  TODO: test basics:
//  - [X] return N, with N == len(path).
//  - [X] return -1 <==> no path
//  - [X] return 0  <==> S == T
//  - [X] if len(path) > len(buffer), buffer is not looked at.
//
//  TODO: test functionality:
//  - [X] does the code complete the task?
//  - [X] does the code crash on edge cases?
//  - [ ] could it work in a multi-threaded environment?
//
//  TODO: test code quality:
//  - [X] how long is the solution?
//  - [X] does it have comments?
//  - [ ] how readable is the code? extract some functions.
//  - [ ] is it well structured? use struct or class for points.
//
//  TODO: test performance:
//  - [ ] how well does the solution perform?
//  - [ ] other outstanding features.
//
//  TODO: write additional tests for good input:
//  - [X] target on wall tile.
//  - [X] start on wall tile.
//  - [X] target is surrounded by walls (and is not wall itself).
//  - [X] target is surrounded by walls and is wall itself.
//  - [X] start is surrounded by walls and is wall itself.
//  - [X] start node and target node are the same (return path length of 0).
//  - [X] test very small mazes.
//  - [X] test very long mazes.
//  - [X] test very big mazes.
//
//  TODO: write additional tests for bad input:
//  - [X] start or target are not within the map.
//  - [X] width or height span a square which is smaller than map.
//  - [X] buffer size is negative.
//  - [X] width or height span a square which is bigger than map.
//

namespace {
bool TEST_PRINT = true;

} // namespace

void TestPrintMaze(const int sx, const int sy, const int tx, const int ty,
                   const unsigned char *map, const int w, const int h,
                   int *buffer, const int size, int cost) {
  if (TEST_PRINT) {
    PrintMaze(sx, sy, tx, ty, map, w, h, buffer, size, cost);
  }
}

//////////////////////////////////////////////////////////////////////////////
/// TESTS WITH  ISSUES
//////////////////////////////////////////////////////////////////////////////

TEST(PathfindTest, MyPathLongerThanBuffer1) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |1 S 1|
  // y 1 |1 1 1|
  //   2 |1 T 1|
  //     +-----+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1, 1, 1,
      1, 1, 1,
      1, 1, 1
      // clang-format on
  };
  int sx = 1;
  int sy = 0;
  int tx = 1;
  int ty = 2;
  int w = 3;
  int h = 3;
  int size = 0;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 2);
  // NOTE: Do not look at the buffer, because the path is shorter than the
  // buffer. Meaning, if len(path) > len(buffer), buffer is not looked at.
  // This cannot be tested.
}

//////////////////////////////////////////////////////////////////////////////
/// TEST HUGE MAP EDGE CASES
//////////////////////////////////////////////////////////////////////////////

TEST(PathfindTest, MyHugeMap3) {
  // data.
  int w = 200;
  int h = 200;
  int map_size = w * h;
  // Make a very big map.
  unsigned char pMap[map_size];
  for (int i = 0; i < map_size; i++) {
    pMap[i] = 1;
  }
  int sx = 0;
  int sy = 0;
  int tx = w - 1;
  int ty = h - 1;
  int size = map_size;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  // test.
  EXPECT_EQ(result, w + h - 2);
}

TEST(PathfindTest, MyHugeMap2) {
  // data.
  int w = 150;
  int h = 150;
  int map_size = w * h;
  // Make a very big map.
  unsigned char pMap[map_size];
  for (int i = 0; i < map_size; i++) {
    pMap[i] = 1;
  }
  int sx = 0;
  int sy = 0;
  int tx = w - 1;
  int ty = h - 1;
  int size = map_size;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  // test.
  EXPECT_EQ(result, w + h - 2);
}

TEST(PathfindTest, MyHugeMap1) {
  // data.
  int w = 100;
  int h = 100;
  int map_size = w * h;
  // Make a very big map.
  unsigned char pMap[map_size];
  for (int i = 0; i < map_size; i++) {
    pMap[i] = 1;
  }
  int sx = 0;
  int sy = 0;
  int tx = w - 1;
  int ty = h - 1;
  int size = map_size;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  // test.
  EXPECT_EQ(result, w + h - 2);
}

TEST(PathfindTest, MyHugeMap0) {
  // data.
  int w = 50;
  int h = 50;
  int map_size = w * h;
  // Make a very big map.
  unsigned char pMap[map_size];
  for (int i = 0; i < map_size; i++) {
    pMap[i] = 1;
  }
  int sx = 0;
  int sy = 0;
  int tx = w - 1;
  int ty = h - 1;
  int size = map_size;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  // test.
  EXPECT_EQ(result, w + h - 2);
}

//////////////////////////////////////////////////////////////////////////////
/// TEST MALFORMED INPUT
//////////////////////////////////////////////////////////////////////////////

TEST(PathfindTest, MyInvalidInput_WidthAndHeightSpanBiggerThanMap2) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 1;
  int ty = 1;
  int w = 10;
  int h = 10;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_WidthAndHeightSpanBiggerThanMap1) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 1;
  int ty = 1;
  int w = 10;
  int h = 10;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_WidthAndHeightSpanSmallerThanMap5) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 1;
  int ty = 1;
  int w = 0;
  int h = 0;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_WidthAndHeightSpanSmallerThanMap4) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 1;
  int ty = 1;
  int w = -1;
  int h = -1;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_WidthAndHeightSpanSmallerThanMap3) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 1;
  int ty = 1;
  int w = 1;
  int h = 1;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_WidthAndHeightSpanSmallerThanMap2) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 0;
  int ty = 0;
  int w = 1;
  int h = 1;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_WidthAndHeightSpanSmallerThanMap1) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 1;
  int ty = 1;
  int w = 2;
  int h = 2;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_WidthAndHeightSpanSmallerThanMap0) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 1;
  int ty = 1;
  int w = 2;
  int h = 2;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_BufferSizeNegative0) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 0;
  int ty = 0;
  int w = 3;
  int h = 3;
  int size = -1;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_TargetNegative3) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = INT_MIN;
  int ty = 0;
  int w = 3;
  int h = 3;
  int size = 20;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_TargetNegative2) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = -1;
  int ty = 0;
  int w = 3;
  int h = 3;
  int size = 20;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_TargetNegative) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 0;
  int ty = -1;
  int w = 3;
  int h = 3;
  int size = 20;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_StartTooBig) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 1000;
  int sy = 1000;
  int tx = 1;
  int ty = 1;
  int w = 3;
  int h = 3;
  int size = 20;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_StartNegative3) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = INT_MIN;
  int tx = 0;
  int ty = 0;
  int w = 3;
  int h = 3;
  int size = 20;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_StartNegative2) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = -1;
  int tx = 0;
  int ty = 0;
  int w = 3;
  int h = 3;
  int size = 20;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_StartNegative) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = -1;
  int sy = 0;
  int tx = 0;
  int ty = 0;
  int w = 3;
  int h = 3;
  int size = 20;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyInvalidInput_AllValid) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1,
      1,1,1,
      1,1,1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 1;
  int ty = 1;
  int w = 3;
  int h = 3;
  int size = 20;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 2);
}

//////////////////////////////////////////////////////////////////////////////
/// TEST EDGE CASES
//////////////////////////////////////////////////////////////////////////////

TEST(PathfindTest, MyLargeMap1) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,0,0, 1,1,1, 1,1,1, 0,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,0,0, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,0,0, 0,0,0, 0,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      //
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      //
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1,
      1,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,0, 1,0,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,0, 1,1,1,
      1,1,1, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,0, 1,0,0,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,0, 1,1,1,
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 29;
  int ty = 29;
  int w = 30;
  int h = 30;
  int size = 1000;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 64);
}

TEST(PathfindTest, MyLargeMap0) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      //
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      //
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 29;
  int ty = 29;
  int w = 30;
  int h = 30;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 56);
}

TEST(PathfindTest, MyLongMaze1) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      // clang-format on
  };
  int sx = 10;
  int sy = 0;
  int tx = 290;
  int ty = 0;
  int w = 300;
  int h = 1;
  int size = 1000;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  // TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 280);
}

TEST(PathfindTest, MyLongMaze0) {
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
      // clang-format on
  };
  int sx = 0;
  int sy = 10;
  int tx = 0;
  int ty = 290;
  int w = 1;
  int h = 300;
  int size = 1000;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  // TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 280);
}

TEST(PathfindTest, MySmallestMaze1) {
  //      x
  //      0
  //     +-+
  // y 0 |X|
  //     +-+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      0
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 0;
  int ty = 0;
  int w = 1;
  int h = 1;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 0);
}

TEST(PathfindTest, MySmallestMaze0) {
  //      x
  //      0
  //     +-+
  // y 0 |X|
  //     +-+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 0;
  int ty = 0;
  int w = 1;
  int h = 1;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 0);
}

TEST(PathfindTest, MySmallMaze4) {
  //       x
  //      0 1
  //     +---+
  //   0 |T 0|
  // y 1 |0 S|
  //     +---+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      0, 0,
      0, 0
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 0;
  int ty = 0;
  int w = 2;
  int h = 2;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MySmallMaze3) {
  //       x
  //      0 1
  //     +---+
  //   0 |T 0|
  // y 1 |0 S|
  //     +---+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1, 0,
      0, 1
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 0;
  int ty = 0;
  int w = 2;
  int h = 2;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MySmallMaze2) {
  //       x
  //      0 1
  //     +---+
  //   0 |T 1|
  // y 1 |0 S|
  //     +---+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1, 1,
      0, 1
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 0;
  int ty = 0;
  int w = 2;
  int h = 2;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 2);
}

TEST(PathfindTest, MySmallMaze1) {
  //       x
  //      0 1
  //     +---+
  //   0 |S 1|
  // y 1 |0 T|
  //     +---+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1, 1,
      0, 1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 1;
  int ty = 1;
  int w = 2;
  int h = 2;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 2);
}

TEST(PathfindTest, MySmallMaze0) {
  //       x
  //      0 1
  //     +---+
  //   0 |S 1|
  // y 1 |1 T|
  //     +---+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1, 1,
      1, 1
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 1;
  int ty = 1;
  int w = 2;
  int h = 2;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 2);
}

TEST(PathfindTest, MyTargetNotReachable3) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,1,0,1,1,//2
        1,1,1,1,0,1,0,1,//3  y
        1,1,1,1,1,0,1,1,//4
        1,1,1,1,1,1,1,1,//5
        1,1,1,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 4;
  int sy = 2;
  int tx = 5;
  int ty = 3;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = -1;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyTargetNotReachable2) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,1,0,1,1,//2
        1,1,1,1,0,1,0,1,//3  y
        1,1,1,1,1,0,1,1,//4
        1,1,1,1,1,1,1,1,//5
        1,1,1,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 5;
  int sy = 3;
  int tx = 4;
  int ty = 2;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = -1;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyTargetNotReachable1) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,1,1,1,1,//2
        1,1,1,1,1,1,1,1,//3  y
        1,1,1,1,1,1,1,1,//4
        1,1,1,1,1,1,1,0,//5
        1,1,1,1,1,1,0,1,//6
      // clang-format on
  };
  int sx = 2;
  int sy = 2;
  int tx = 7;
  int ty = 6;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = -1;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyStartAndTargetAreSameAndOnWallTile) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |0 0 0|
  // y 1 |0 X 0|
  //   2 |0 0 0|
  //     +-----+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      0,0,0,
      0,0,0,
      0,0,0
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 1;
  int ty = 1;
  int w = 3;
  int h = 3;
  int size = 7;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 0);
}

TEST(PathfindTest, MyStartAndTargetAreSame4) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,1,0,1,1,//2
        1,1,1,1,0,1,0,1,//3  y
        1,1,1,1,1,0,1,1,//4
        1,1,1,1,1,1,1,1,//5
        1,1,1,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 5;
  int sy = 3;
  int tx = 5;
  int ty = 3;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = 0;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyStartAndTargetAreSame3) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,1,0,1,1,//2
        1,1,1,1,0,1,0,1,//3  y
        1,1,1,1,1,0,1,1,//4
        1,1,1,1,1,1,1,1,//5
        1,1,1,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 4;
  int sy = 2;
  int tx = 4;
  int ty = 2;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = 0;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyStartAndTargetAreSame2) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |0 0 0|
  // y 1 |0 X 0|
  //   2 |0 0 0|
  //     +-----+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      0, 0, 0,
      0, 1, 0,
      0, 0, 0
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 1;
  int ty = 1;
  int w = 3;
  int h = 3;
  int size = 7;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 0);
}

TEST(PathfindTest, MyStartAndTargetAreSame1) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |1 1 1|
  // y 1 |1 X 1|
  //   2 |1 1 1|
  //     +-----+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1, 1, 1,
      1, 1, 1,
      1, 1, 1
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 1;
  int ty = 1;
  int w = 3;
  int h = 3;
  int size = 7;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 0);
}

TEST(PathfindTest, MyStartAndTargetIsWall1) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |0 0 0|
  // y 1 |0 S T|
  //   2 |0 0 0|
  //     +-----+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      0,0,0,
      0,0,0,
      0,0,0
      // clang-format on
  };
  int sx = 1;
  int sy = 1;
  int tx = 2;
  int ty = 1;
  int w = 3;
  int h = 3;
  int size = 7;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyStartIsWall3) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,0,0,0,1,//2
        1,1,1,1,0,0,0,1,//3  y
        1,1,1,1,0,0,0,1,//4
        1,1,1,1,1,1,1,1,//5
        1,1,1,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 5;
  int sy = 3;
  int tx = 3;
  int ty = 3;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = -1;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyStartIsWall2) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,1,1,1,1,//2
        1,1,1,1,1,0,1,1,//3  y
        1,1,1,1,1,1,1,1,//4
        1,1,1,1,1,1,1,1,//5
        1,1,1,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 5;
  int sy = 3;
  int tx = 3;
  int ty = 3;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = -1;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyStartIsWall1) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |1 T 1|
  // y 1 |1 1 1|
  //   2 |1 S 1|
  //     +-----+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1, 1, 1,
      1, 1, 1,
      1, 0, 1
      // clang-format on
  };
  int sx = 1;
  int sy = 2;
  int tx = 1;
  int ty = 0;
  int w = 3;
  int h = 3;
  int size = 7;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

TEST(PathfindTest, MyTargetIsWall3) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,0,0,0,1,//2
        1,1,1,1,0,0,0,1,//3  y
        1,1,1,1,0,0,0,1,//4
        1,1,1,1,1,1,1,1,//5
        1,1,1,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 3;
  int sy = 3;
  int tx = 5;
  int ty = 3;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = -1;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyTargetIsWall2) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,1,1,1,1,1,1,//0
        1,1,1,1,1,1,1,1,//1
        1,1,1,1,1,1,1,1,//2
        1,1,1,1,1,0,1,1,//3  y
        1,1,1,1,1,1,1,1,//4
        1,1,1,1,1,1,1,1,//5
        1,1,1,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 3;
  int sy = 3;
  int tx = 5;
  int ty = 3;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = -1;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyTargetIsWall1) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |1 S 1|
  // y 1 |1 1 1|
  //   2 |1 T 1|
  //     +-----+
  // data.
  unsigned char pMap[] = {
      // clang-format off
      1, 1, 1,
      1, 1, 1,
      1, 0, 1
      // clang-format on
  };
  int sx = 1;
  int sy = 0;
  int tx = 1;
  int ty = 2;
  int w = 3;
  int h = 3;
  int size = 7;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

//////////////////////////////////////////////////////////////////////////////
/// TEST INVALID MAZES
//////////////////////////////////////////////////////////////////////////////

TEST(PathfindTest, Example2) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |0 0 S|
  // y 1 |0 1 1|
  //   2 |T 0 1|
  //     +-----+
  // data.
  unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
  int sx = 2;
  int sy = 0;
  int tx = 0;
  int ty = 2;
  int w = 3;
  int h = 3;
  int size = 7;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, -1);
}

//////////////////////////////////////////////////////////////////////////////
/// TEST PATHFINDING
//////////////////////////////////////////////////////////////////////////////

TEST(PathfindTest, Example1) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |S X 1 1|
  // y 1 |0 X 0 1|
  //   2 |0 T 1 1|
  //     +-------+
  // data.
  unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
  int sx = 0;
  int sy = 0;
  int tx = 1;
  int ty = 2;
  int w = 4;
  int h = 3;
  int size = 12;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 3);
  EXPECT_EQ(pOutBuffer[0], 1);
  EXPECT_EQ(pOutBuffer[1], 5);
  EXPECT_EQ(pOutBuffer[2], 9);
}

TEST(PathfindTest, MyTest1A) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |1 1 1|
  // y 1 |1 1 1|
  //   2 |S 0 T|
  //     +-----+
  unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 0, 1};
  int sx = 0;
  int sy = 2;
  int tx = 2;
  int ty = 2;
  int w = 3;
  int h = 3;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 4);
  EXPECT_EQ(pOutBuffer[0], 3);
  EXPECT_EQ(pOutBuffer[1], 4);
  EXPECT_EQ(pOutBuffer[2], 5);
  EXPECT_EQ(pOutBuffer[3], 8);
}

TEST(PathfindTest, MyTest1B) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |T 0 1|
  // y 1 |1 1 1|
  //   2 |1 0 S|
  //     +-----+
  unsigned char pMap[] = {1, 0, 1, 1, 1, 1, 1, 0, 1};
  int sx = 2;
  int sy = 2;
  int tx = 0;
  int ty = 0;
  int w = 3;
  int h = 3;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 4);
  EXPECT_EQ(pOutBuffer[0], 5);
  EXPECT_EQ(pOutBuffer[1], 4);
  EXPECT_EQ(pOutBuffer[2], 3);
  EXPECT_EQ(pOutBuffer[3], 0);
}

TEST(PathfindTest, MyTest2) {
  //         x
  //      0 1 2
  //     +-----+
  //   0 |1 1 1|
  // y 1 |1 0 1|
  //   2 |S 0 T|
  //     +-----+
  unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 1, 0, 1};
  int sx = 0;
  int sy = 2;
  int tx = 2;
  int ty = 2;
  int w = 3;
  int h = 3;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 6);
  EXPECT_EQ(pOutBuffer[0], 3);
  EXPECT_EQ(pOutBuffer[1], 0);
  EXPECT_EQ(pOutBuffer[2], 1);
  EXPECT_EQ(pOutBuffer[3], 2);
  EXPECT_EQ(pOutBuffer[4], 5);
  EXPECT_EQ(pOutBuffer[5], 8);
}

TEST(PathfindTest, MyTest3) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |S 1 1 T|
  // y 1 |1 1 1 1|
  //   2 |1 1 1 1|
  //   3 |1 1 1 1|
  //     +-------+
  unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int sx = 0;
  int sy = 0;
  int tx = 3;
  int ty = 0;
  int w = 4;
  int h = 4;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 3);
  EXPECT_EQ(pOutBuffer[0], 1);
  EXPECT_EQ(pOutBuffer[1], 2);
  EXPECT_EQ(pOutBuffer[2], 3);
}

TEST(PathfindTest, MyTest3A) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |1 1 1 1|
  // y 1 |S 1 1 T|
  //   2 |1 1 1 1|
  //   3 |1 1 1 1|
  //     +-------+
  unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int sx = 0;
  int sy = 1;
  int tx = 3;
  int ty = 1;
  int w = 4;
  int h = 4;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 3);
  EXPECT_EQ(pOutBuffer[0], 5);
  EXPECT_EQ(pOutBuffer[1], 6);
  EXPECT_EQ(pOutBuffer[2], 7);
}

TEST(PathfindTest, MyTest3B) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |1 1 1 1|
  // y 1 |1 1 1 1|
  //   2 |S 1 1 T|
  //   3 |1 1 1 1|
  //     +-------+
  unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int sx = 0;
  int sy = 2;
  int tx = 3;
  int ty = 2;
  int w = 4;
  int h = 4;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 3);
  EXPECT_EQ(pOutBuffer[0], 9);
  EXPECT_EQ(pOutBuffer[1], 10);
  EXPECT_EQ(pOutBuffer[2], 11);
}

TEST(PathfindTest, MyTest4) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |S 0 1 T|
  // y 1 |1 1 0 1|
  //   2 |1 0 0 1|
  //   3 |1 1 1 1|
  //     +-------+
  unsigned char pMap[] = {
      // clang-format off
    1, 0, 1, 1,
    1, 1, 0, 1,
    1, 0, 0, 1,
    1, 1, 1, 1,
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 3;
  int ty = 0;
  int w = 4;
  int h = 4;
  int size = 30;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 9);
  EXPECT_EQ(pOutBuffer[0], 4);
  EXPECT_EQ(pOutBuffer[1], 8);
  EXPECT_EQ(pOutBuffer[2], 12);
  EXPECT_EQ(pOutBuffer[3], 13);
  EXPECT_EQ(pOutBuffer[4], 14);
  EXPECT_EQ(pOutBuffer[5], 15);
  EXPECT_EQ(pOutBuffer[6], 11);
  EXPECT_EQ(pOutBuffer[7], 7);
  EXPECT_EQ(pOutBuffer[8], 3);
}

TEST(PathfindTest, MyTest4B) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |1 1 1 1|
  // y 1 |S 0 0 T|
  //   2 |1 0 0 1|
  //   3 |1 1 1 1|
  //     +-------+
  unsigned char pMap[] = {
      // clang-format off
    1, 1, 1, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 1, 1, 1,
      // clang-format on
  };
  int sx = 0;
  int sy = 1;
  int tx = 3;
  int ty = 1;
  int w = 4;
  int h = 4;
  int size = 14;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 5);
  EXPECT_EQ(pOutBuffer[0], 0);
  EXPECT_EQ(pOutBuffer[1], 1);
  EXPECT_EQ(pOutBuffer[2], 2);
  EXPECT_EQ(pOutBuffer[3], 3);
  EXPECT_EQ(pOutBuffer[4], 7);
}

TEST(PathfindTest, MyTest4C) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |1 1 1 1|
  // y 1 |1 0 0 1|
  //   2 |S 0 0 T|
  //   3 |1 1 1 1|
  //     +-------+
  unsigned char pMap[] = {
      // clang-format off
    1, 1, 1, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 1, 1, 1,
      // clang-format on
  };
  int sx = 0;
  int sy = 2;
  int tx = 3;
  int ty = 2;
  int w = 4;
  int h = 4;
  int size = 14;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 5);
  EXPECT_EQ(pOutBuffer[0], 12);
  EXPECT_EQ(pOutBuffer[1], 13);
  EXPECT_EQ(pOutBuffer[2], 14);
  EXPECT_EQ(pOutBuffer[3], 15);
  EXPECT_EQ(pOutBuffer[4], 11);
}

TEST(PathfindTest, MyTest4D) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |1 1 1 1|
  // y 1 |1 0 0 1|
  //   2 |1 0 0 T|
  //   3 |S 1 1 0|
  //     +-------+
  unsigned char pMap[] = {
      // clang-format off
    1, 1, 1, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 1, 1, 0,
      // clang-format on
  };
  int sx = 0;
  int sy = 3;
  int tx = 3;
  int ty = 2;
  int w = 4;
  int h = 4;
  int size = 14;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 8);
  EXPECT_EQ(pOutBuffer[0], 8);
  EXPECT_EQ(pOutBuffer[1], 4);
  EXPECT_EQ(pOutBuffer[2], 0);
  EXPECT_EQ(pOutBuffer[3], 1);
  EXPECT_EQ(pOutBuffer[4], 2);
  EXPECT_EQ(pOutBuffer[5], 3);
  EXPECT_EQ(pOutBuffer[6], 7);
  EXPECT_EQ(pOutBuffer[7], 11);
}

TEST(PathfindTest, MyTest4E) {
  //         x
  //      0 1 2 3
  //     +-------+
  //   0 |1 1 1 1|
  // y 1 |1 1 0 1|
  //   2 |S 0 0 T|
  //   3 |1 1 1 1|
  //     +-------+
  unsigned char pMap[] = {
      // clang-format off
    1, 1, 1, 1,
    1, 1, 0, 1,
    1, 0, 0, 1,
    1, 1, 1, 1,
      // clang-format on
  };
  int sx = 0;
  int sy = 2;
  int tx = 3;
  int ty = 2;
  int w = 4;
  int h = 4;
  int size = 14;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  EXPECT_EQ(result, 5);
  EXPECT_EQ(pOutBuffer[0], 12);
  EXPECT_EQ(pOutBuffer[1], 13);
  EXPECT_EQ(pOutBuffer[2], 14);
  EXPECT_EQ(pOutBuffer[3], 15);
  EXPECT_EQ(pOutBuffer[4], 11);
}

TEST(PathfindTest, MyTest5) {
  //          x
  //      0 1 2 3 4
  //     +---------+
  //   0 |S 0 1 1 1|
  //   1 |1 1 1 0 1|
  // y 2 |0 1 0 1 1|
  //   3 |T 0 1 0 1|
  //   4 |1 1 1 1 1|
  //     +---------+
  unsigned char pMap[] = {
      // clang-format off
        1, 0, 1, 1, 1,
        1, 1, 1, 0, 1,
        0, 1, 0, 1, 1,
        1, 0, 1, 0, 1,
        1, 1, 1, 1, 1,
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 0;
  int ty = 3;
  int w = 5;
  int h = 5;
  int size = 50;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = 15;
  EXPECT_EQ(result, path_len);
  int expected[] = {5, 6, 7, 2, 3, 4, 9, 14, 19, 24, 23, 22, 21, 20, 15};
  for (int i = 0; i < path_len; i++) {
    EXPECT_EQ(pOutBuffer[i], expected[i]);
  }
}

TEST(PathfindTest, MyTest6) {
  //          x
  //      0 1 2 3 4
  //     +---------+
  //   0 |S 0 1 1 1|
  //   1 |1 1 1 0 1|
  // y 2 |0 1 0 1 1|
  //   3 |T 0 1 0 1|
  //   4 |1 1 1 1 1|
  //     +---------+
  unsigned char pMap[] = {
      // clang-format off
        1, 0, 1, 1, 1,
        1, 1, 1, 0, 1,
        0, 1, 0, 1, 1,
        1, 0, 1, 0, 1,
        1, 1, 1, 1, 1,
      // clang-format on
  };
  int sx = 0;
  int sy = 3;
  int tx = 0;
  int ty = 0;
  int w = 5;
  int h = 5;
  int size = 50;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = 15;
  EXPECT_EQ(result, path_len);
  int expected[] = {20, 21, 22, 23, 24, 19, 14, 9, 4, 3, 2, 7, 6, 5, 0};
  for (int i = 0; i < path_len; i++) {
    EXPECT_EQ(pOutBuffer[i], expected[i]);
  }
}

TEST(PathfindTest, MyTest7A) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,0,1,1,1,1,1,//0
        1,0,0,1,0,1,0,1,//1
        1,1,1,1,0,0,1,1,//2
        1,0,1,0,1,1,1,0,//3  y
        0,1,0,1,1,0,1,1,//4
        1,1,1,1,0,1,0,1,//5
        1,1,0,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 2;
  int ty = 2;
  int w = 8;
  int h = 7;
  int size = 10;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = 4;
  EXPECT_EQ(result, path_len);
  int expected[] = {8, 16, 17, 18};
  for (int i = 0; i < path_len; i++) {
    EXPECT_EQ(pOutBuffer[i], expected[i]);
  }
}

TEST(PathfindTest, MyTest7B) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,0,1,1,1,1,1,//0
        1,0,0,1,0,1,0,1,//1
        1,1,1,1,0,0,1,1,//2
        1,0,1,0,1,1,1,0,//3  y
        0,1,0,1,1,0,1,1,//4
        1,1,1,1,0,1,0,1,//5
        1,1,0,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 5;
  int ty = 5;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = 22;
  EXPECT_EQ(result, path_len);
}

TEST(PathfindTest, MyTest7C) {
  unsigned char pMap[] = {
      // clang-format off
      //       x
      //0 1 2 3 4 5 6 7
        1,1,0,1,1,1,1,1,//0
        1,0,0,1,0,1,0,1,//1
        1,1,1,1,0,0,1,1,//2
        1,0,1,0,1,1,1,0,//3  y
        0,1,0,1,1,0,1,1,//4
        1,1,1,1,0,1,0,1,//5
        1,1,0,1,1,1,1,1,//6
      // clang-format on
  };
  int sx = 0;
  int sy = 0;
  int tx = 1;
  int ty = 6;
  int w = 8;
  int h = 7;
  int size = 100;
  // execute.
  int pOutBuffer[size];
  int result = FindPath(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size);
  TestPrintMaze(sx, sy, tx, ty, pMap, w, h, pOutBuffer, size, result);
  // test.
  int path_len = 23;
  EXPECT_EQ(result, path_len);
}
