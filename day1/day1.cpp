#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <unordered_map>
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

std::unordered_map<int, int> countOccurences(std::vector<int> &vec) {
  std::unordered_map<int, int> mappedVector;

  for (int entry : vec) {
    mappedVector[entry]++;
  }

  // Print the counts
  // for (const auto &pair : mappedVector) {
  //   std::cout << pair.first << ": " << pair.second << std::endl;
  // }

  return mappedVector;
}

int similarityScore(std::vector<int> &column1, std::vector<int> &column2) {

  int simScore = 0;

  std::unordered_map<int, int> occurencesMapColumn2 = countOccurences(column2);
  std::vector<int> weightedColumn1; // weighted by sim score of col2

  for (size_t i = 0; i < column1.size(); ++i) {
    if (auto search = occurencesMapColumn2.find(column1[i]);
        search != occurencesMapColumn2.end()) {
      if (search->first > 1) {
        weightedColumn1.push_back(column1[i] * search->second);
      }
    } else {
      weightedColumn1.push_back(0);
    }
  }

  for (int num : weightedColumn1) {
    simScore += num;
  }

  return simScore;
}

int main() {
  std::vector<int> column1, column2;
  readInput("input_day1.txt", column1, column2);

  // Part 1: Sort ascending and compute diff and sum vector
  std::vector<int> ascendingColumn1 = sortAscending(column1);
  std::vector<int> ascendingColumn2 = sortAscending(column2);

  std::vector<int> diffVec =
      vectorDifference(ascendingColumn1, ascendingColumn2);

  int diffSum = 0;

  for (int num : diffVec) {
    diffSum += num;
  }

  std::cout << "Difference: " << diffSum << std::endl;

  // Part 2: Compute similarity score and and multiply column1 entries by it
  int simScoreColumn1 = similarityScore(column1, column2);
  std::cout << "Similarity score: " << simScoreColumn1 << std::endl;

  return 0;
}
