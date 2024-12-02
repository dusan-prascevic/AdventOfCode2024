#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

int readInput(const std::string &filename, std::vector<int> &column1,
              std::vector<int> &column2) {

  std::ifstream inputFile(filename);

  if (inputFile.is_open()) {
    int num1, num2;
    while (inputFile >> num1 >> num2) {

      column1.push_back(num1);
      column2.push_back(num2);
    }
  }

  inputFile.close();

  // Print the vectors to the output
  // for (size_t i = 0; i < column1.size(); ++i) {
  //   std::cout << column1[i] << " " << column2[i] << std::endl;
  // }

  return 0;
}

std::vector<int> sortAscending(std::vector<int> &vec) {
  std::vector<int> sortedVec = vec;
  sort(sortedVec.begin(), sortedVec.end());

  return sortedVec;
}

std::vector<int> vectorDifference(std::vector<int> &vec1,
                                  std::vector<int> &vec2) {

  std::vector<int> differenceVec;

  // check if two vectors are the same size
  if (vec1.size() == vec2.size()) {
    for (size_t i = 0; i < vec1.size(); ++i) {
      differenceVec.push_back(std::abs(vec1[i] - vec2[i]));
    }

    // std::cout << "Difference vector: " << std::endl;
    //
    // for (size_t i = 0; i < differenceVec.size(); ++i) {
    //   std::cout << differenceVec[i] << std::endl;
    // }
  }

  else {
    std::cout << "Two vectors are not the same size, exiting." << std::endl;
  }

  return differenceVec;
}

int main() {
  std::vector<int> column1, column2;

  readInput("input_day1.txt", column1, column2);

  std::vector<int> ascendingColumn1 = sortAscending(column1);
  std::vector<int> ascendingColumn2 = sortAscending(column2);

  std::vector<int> diffVec =
      vectorDifference(ascendingColumn1, ascendingColumn2);

  int diffSum = 0;

  for (int num : diffVec) {
    diffSum += num;
  }

  std::cout << "Difference: " << diffSum << std::endl;

  // for (size_t i = 0; i < ascendingColumn1.size(); ++i) {
  //   std::cout << ascendingColumn1[i] << " " << ascendingColumn2[i] <<
  //   std::endl;
  // }

  return 0;
}
