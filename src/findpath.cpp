
#include <algorithm>
#include <vector>

namespace {
const int neighbors_x[4] = {0, 1, 0, -1};
const int neighbors_y[4] = {1, 0, -1, 0};
} // END OF namespace

///////////////////////////////////////////////////////////////////////////////
/// FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

/**
 * @param[out] neighbors The neighboring 4 cells for the coordinates x and y.
 * @param[in] x The x coordinate for which to calculate the neighbors.
 * @param[in] y The y coordinate for which to calculate the neighbors.
 * @param[in] width The width of the maze.
 * @param[in] heigh The heigh of the maze.
 */
void SetNeighbors(int *neighbors, int x, int y, int width, int height) {
  for (int i = 0; i < 4; i++) {
    int neighborX = neighbors_x[i] + x;
    int neighborY = neighbors_y[i] + y;
    bool isWithinX = neighborX >= 0 && neighborX < width;
    bool isWithinY = neighborY >= 0 && neighborY < height;
    neighbors[i] = -1;
    if (isWithinX && isWithinY) {
      // Convert coordinates to index.
      neighbors[i] = neighborY * width + neighborX;
    }
  }
}

/**
 * @param[in] vec The vector to search for an element.
 * @param[in] element The element to find within the vector.
 * @return The first index at which element appears.
 */
bool Contains(std::vector<int> vec, int element) {
  return std::find(vec.begin(), vec.end(), element) != vec.end();
}

///////////////////////////////////////////////////////////////////////////////
/// ASTAR
///////////////////////////////////////////////////////////////////////////////

/**
 * @param[in] sx The x coordinate of the start node.
 * @param[in] sy The y coordinate of the start node.
 * @param[in] tx The x coordinate of the target node.
 * @param[in] ty The y coordinate of the target node.
 * @param[in] map The map as an array of integers (1 for passable tiles, 0 for
 * wall tiles).
 * @param[in] width The width of the maze.
 * @param[in] height The height of the maze.
 * @param[out] buffer A list of the indexes of the path (including the target,
 * but excluding the start).
 * @param[in] buffer_size The length of the output buffer.
 * @return The length of a path, if found. Otherwise 0 if start and target have
 * the same coordinates, -1 if no path was found or indexes are out of bounds.
 */
int FindPath(const int sx, const int sy, const int tx, const int ty,
             const unsigned char *map, const int width, const int height,
             int *buffer, const int buffer_size) {

  // Get index of start and target node.
  int startNode = sy * width + sx;  // Convert coordinates to index.
  int targetNode = ty * width + tx; // Convert coordinates to index.

  // Abort on negative buffer size.
  if (buffer_size < 0) {
    return -1;
  }
  // Abort if start or target out of lower bounds.
  if (sx < 0 || sy < 0 || tx < 0 || ty < 0) {
    return -1;
  }
  // Abort if start or target out of upper bounds.
  if (sx >= width || sy >= height || tx >= width || ty >= height) {
    return -1;
  }
  // Abort if start or target are the same.
  if (sx == tx && sy == ty) {
    return 0;
  }
  // Abort if start or target are inside wall.
  if (map[startNode] == 0 || map[targetNode] == 0) {
    return -1;
  }

  // Initialize an masks for the map: forward costs, backward costs and
  // parents.
  const int arrSize = width * height;
  unsigned int fwd[arrSize];
  unsigned int bwd[arrSize];
  unsigned int parents[arrSize];
  for (int i = 0; i < arrSize; i++) {
    fwd[i] = 0;
    bwd[i] = 0;
    parents[i] = 0;
  }

  // Initialize a list of indexes for the visited and processed nodes.
  std::vector<int> todos;
  std::vector<int> dones;

  // Start at the start node.
  todos.push_back(startNode);

  // While there is nodes to process.
  while (todos.size() > 0) {

    // Chose the node with the lowest total cost as current node.
    int current = todos[0];
    int better_index = 0;
    int index = 0;
    for (int todo : todos) {

      // Find node with lowest total costs, but if total costs are the same,
      // find lowest forward costs.
      bool hasLessTotal = fwd[todo] + bwd[todo] < fwd[current] + bwd[current];
      bool hasEqualTotal = fwd[todo] + bwd[todo] == fwd[current] + bwd[current];
      bool hasLessForward = fwd[todo] < fwd[current];
      if (hasLessTotal || (hasEqualTotal && hasLessForward)) {
        current = todo;
        better_index = index;
      }
      index++;
    }
    int cx = current % width;
    int cy = current / width;

    // Update done list and todo list.
    dones.push_back(current);
    // Remove current node from todo list.
    // TODO: this is inefficient for large vectors.
    todos.erase(todos.begin() + better_index);

    // Get indexes of all neighbors (-1 if neighbor is outside of map).
    int neighbors[4];
    SetNeighbors(neighbors, cx, cy, width, height);

    // Have a look at all neighbors.
    for (int i = 0; i < 4; i++) {
      int neighbor = neighbors[i];
      int nx = neighbor % width;
      int ny = neighbor / width;

      // Check if neighbor is in bounds, not a wall and not done.
      bool isWithinBounds = neighbor >= 0;
      bool isNoWall = isWithinBounds ? map[neighbor] != 0 : false;
      bool isNotDone = !Contains(dones, neighbor);
      if (isWithinBounds && isNoWall && isNotDone) {

        // Have a look at all neighbors that have not been processed yet.
        bool isNotTodo = !Contains(todos, neighbor);
        float costToNeighborFromHere = bwd[current] + 1;
        float costToNeighborSoFar = bwd[neighbor];
        bool hasBetterPath = costToNeighborFromHere < costToNeighborSoFar;
        if (isNotTodo || hasBetterPath) {

          // Update costs and parent if the route is shorter via current node.
          bwd[neighbor] = costToNeighborFromHere;
          parents[neighbor] = current;
          if (isNotTodo) {

            // Estimate distance to taget.
            fwd[neighbor] = abs(nx - tx) + abs(ny - ty);
            // Add node to todo list if it has not been processed yet.
            todos.push_back(neighbor);
          }
        }
      }
    }
  }

  // Get the path length.
  int lastNode = targetNode;
  int pathLength = 0;
  while (bwd[lastNode] > 0) {
    lastNode = parents[lastNode];
    pathLength++;
  }

  // Write shortest path to output.
  int i = pathLength;
  lastNode = targetNode;
  while (i > 0) {
    buffer[i - 1] = lastNode;
    lastNode = parents[lastNode];
    i--;
  }

  // Return the path length, but if start node and target node are not the
  // same.
  bool hasNoPath = pathLength == 0;
  if (hasNoPath) {
    pathLength = -1; // Return -1 for invalid path lengths.
  }
  return pathLength;
}
