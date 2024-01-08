#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class vertexArrow {
private:
  string colour;
  string direction;
  bool exploreStatus;
  int rowIndex;
  int colIndex;
  int vertexID;

public:
  // constructor
  vertexArrow(string &str, int rowI, int colI, int id)
      : colour(""), direction(""), exploreStatus(false), rowIndex(rowI),
        colIndex(colI), vertexID(id) {
    sepInput(str);
  }

  // function to split string input and get colour, direction from it
  void sepInput(const std::string &input) {
    size_t pos = input.find('-');
    if (pos != std::string::npos) {
      colour = input.substr(0, pos);
      direction = input.substr(pos + 1);
    }
  }

  
  // setter function for the attribute we want to be able to change
  void set_exploreStatus(bool in) { exploreStatus = in; }

  // getter functions
  string get_colour() { return colour; }
  string get_direction() { return direction; }
  bool get_exploreStatus() { return exploreStatus; }
  int get_rowIndex() { return rowIndex; }
  int get_colIndex() { return colIndex; }
  int get_vertexID() { return vertexID; }
};

unordered_map<vertexArrow *, vector<vertexArrow *>>
mazeGraph(vector<vector<vertexArrow>> &matrix) {
  unordered_map<vertexArrow *, vector<vertexArrow *>> adjacencyList;
  vector<vertexArrow *> adjacentNodes;
  int rows = matrix.size();
  int cols = matrix[0].size();

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      adjacencyList[&matrix[r][c]] = {};

      string currDirection = matrix[r][c].get_direction();
      string currColour = matrix[r][c].get_colour();
      int currRow = matrix[r][c].get_rowIndex();
      int currCol = matrix[r][c].get_colIndex();

      if (currDirection == "O") {
        adjacentNodes.push_back(nullptr);
      } else {
        vector<vertexArrow *> adjacentNodes = {};
        if (currDirection == "N") {
          for (int i = 0; i < rows; i++) {
            if (matrix[i][c].get_colour() != currColour &&
                matrix[i][c].get_rowIndex() < currRow) {
              adjacentNodes.push_back(&matrix[i][c]);
            }
          }
        } else if (currDirection == "S") {
          for (int i = 0; i < rows; i++) {
            if (matrix[i][c].get_colour() != currColour &&
                matrix[i][c].get_rowIndex() > currRow) {
              adjacentNodes.push_back(&matrix[i][c]);
            }
          }
        } else if (currDirection == "E") {
          for (int i = 0; i < cols; i++) {
            if (matrix[r][i].get_colour() != currColour &&
                matrix[r][i].get_colIndex() > currCol) {
              adjacentNodes.push_back(&matrix[r][i]);
            }
          }
        } else if (currDirection == "W") {
          for (int i = 0; i < cols; i++) {
            if (matrix[r][i].get_colour() != currColour &&
                matrix[r][i].get_colIndex() < currCol) {
              adjacentNodes.push_back(&matrix[r][i]);
            }
          }
        } else if (currDirection == "NE") {
          for (int i = 0; i < min(rows, cols); ++i) {
            int row = currRow - i;
            int col = currCol + i;

            // Check if the current index is within the matrix bounds
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
              adjacentNodes.push_back(nullptr);
              break; // Stop if out of bounds
            }
            if (currColour != matrix[row][col].get_colour()) {
              adjacentNodes.push_back(&matrix[row][col]);
            }
          }
        } else if (currDirection == "SE") {
          for (int i = 0; i < min(rows, cols); ++i) {
            int row = currRow + i;
            int col = currCol + i;

            // Check if the current index is within the matrix bounds
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
              adjacentNodes.push_back(nullptr);
              break; // Stop if out of bounds
            }
            if (currColour != matrix[row][col].get_colour()) {
              adjacentNodes.push_back(&matrix[row][col]);
            }
          }
        } else if (currDirection == "SW") {
          for (int i = 0; i < min(rows, cols); ++i) {
            int row = currRow + i;
            int col = currCol - i;

            // Check if the current index is within the matrix bounds
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
              adjacentNodes.push_back(nullptr);
              break; // Stop if out of bounds
            }
            if (currColour != matrix[row][col].get_colour()) {
              adjacentNodes.push_back(&matrix[row][col]);
            }
          }
        } else if (currDirection == "NW") {
          for (int i = 0; i < min(rows, cols); ++i) {
            int row = currRow - i;
            int col = currCol - i;

            // Check if the current index is within the matrix bounds
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
              adjacentNodes.push_back(nullptr);
              break; // Stop if out of bounds
            }
            if (currColour != matrix[row][col].get_colour()) {
              adjacentNodes.push_back(&matrix[row][col]);
            }
          }
        }
        adjacencyList[&matrix[r][c]] = adjacentNodes;
      }
    }
  }
  return adjacencyList;
}

vector<vertexArrow *>findMazePath(unordered_map<vertexArrow *, vector<vertexArrow *>> &adjacencyList, vertexArrow *origin, vertexArrow *destination) {
  unordered_map<vertexArrow *, int>distance; // to keep track of distances to ensure shortest path found
  unordered_map<vertexArrow *, vertexArrow *>predecessor; // keey track of predecessor nodes to ensure shortest path
  priority_queue<pair<int, vertexArrow *>, vector<pair<int, vertexArrow *>>, greater<pair<int, vertexArrow *>>>pq; //priority queue, smaller = higher priority

  // initialize distances and predecessors
  for (auto &entry : adjacencyList) {
    vertexArrow *vertex = entry.first;
    distance[vertex] = numeric_limits<int>::max();
    predecessor[vertex] = nullptr;
  }

  // for source node set distance to 0 and push to priority queue
  distance[origin] = 0;
  pq.push({0, origin});

  //finding shortest path from origin to all nodes in graph 
  while (!pq.empty()) {
    vertexArrow *current = pq.top().second;
    pq.pop();

    for (vertexArrow *neighbor : adjacencyList[current]) {
      int newDistance = distance[current] + 1;

      if (newDistance < distance[neighbor]) {
        distance[neighbor] = newDistance;
        predecessor[neighbor] = current;
        pq.push({newDistance, neighbor});
      }
    }
  }

  // construct the path from origin to destination
  vector<vertexArrow *> mazePath;
  vertexArrow *current = destination;

  while (current != nullptr) {
    mazePath.insert(mazePath.begin(), current);
    current = predecessor[current];
  }
  
  return mazePath;
}

vector<pair<int, string>>translatePath(vector<vertexArrow *> &path) {
  //initializing vector to store distance, direction pairs
  vector<pair<int, string>> output;
  //for loop to iterate through path vector and translate the consecutive objects into distance and direction
  for (int i = 0; i < path.size(); i++) {
    string currDir = path[i]->get_direction();
    int distance;
    if (currDir == "N") {
      distance = path[i]->get_rowIndex() - path[i + 1]->get_rowIndex();
    } else if (currDir == "S") {
      distance = path[i + 1]->get_rowIndex() - path[i]->get_rowIndex();
    } else if (currDir == "E") {
      distance = path[i + 1]->get_colIndex() - path[i]->get_colIndex();
    } else if (currDir == "W") {
      distance = path[i]->get_colIndex() - path[i + 1]->get_colIndex();
    } else if (currDir == "NE") {
      distance = path[i]->get_rowIndex() - path[i + 1]->get_rowIndex();
    } else if (currDir == "SE") {
      distance = path[i + 1]->get_rowIndex() - path[i]->get_rowIndex();
    } else if (currDir == "SW") {
      distance = path[i + 1]->get_rowIndex() - path[i]->get_rowIndex();
    } else if (currDir == "NW") {
      distance = path[i]->get_rowIndex() - path[i + 1]->get_rowIndex();
    }
    output.push_back(make_pair(distance, currDir));
  }
  output.pop_back(); //remove last element since it gives the distance and direction of the target
  return output;
}

int main() {
  //opening input file
  string filename;
  cout << "Enter the name of the input file: ";
  cin >> filename;
  
  ifstream inFile;
  inFile.open(filename);

  //making sure file is open before continuing
  if (!inFile.is_open()) {
    cout << "Error opening file." << endl;
    return 1;
  }

  //declaring line variable to store each line of the file and matrixArray variable to store the matrix
  string line;
  vector<vector<vertexArrow>> matrixArray;
  
  //storing first line with dimensions of the maze in integers
  int numRows, numCols;
  inFile >> numRows >> numCols;
  int vertexID = 0;

  //for loop to make arrow objects and store each line of the file into a vector
  for (int row = 0; row < numRows; row++) {
    vector<vertexArrow> result;
    for (int col = 0; col < numCols; col++) {
      string word;
      inFile >> word;
      if (word.size() >= 3) {
        vertexArrow temp(word, row, col, vertexID);
        result.push_back(temp);
        vertexID++;
      } else {
        word = "O-O";
        vertexArrow temp(word, row, col, vertexID);
        result.push_back(temp);
        vertexID++;
      }
    }
    matrixArray.push_back(result);
  }
  //calling function to make adjacency list
  unordered_map<vertexArrow *, vector<vertexArrow *>> adjacencyList =mazeGraph(matrixArray);
  
  //calling function to find the optimal path
  vector<vertexArrow *> mazePath = findMazePath(adjacencyList, &matrixArray[0][0], &matrixArray[numRows - 1][numCols - 1]);
  
  //calling function to translate the path into pairs of distance and direction
  vector<pair<int, string>> finalPath = translatePath(mazePath);
  
  // writing final path to output file
  ofstream outFile;
  outFile.open("output.txt");
  if (!outFile.is_open()) {
    cout << "Error opening file." << endl;
    return 1;
  }
  
  for (auto iter: finalPath){ outFile << iter.first << iter.second << " ";}

  cout << "Final path is written in output.txt" << endl;
  // close input file
  inFile.close();
  outFile.close();

  return 0;
}
