#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> readReports(const std::string &filename) {

  std::vector<std::vector<int>> result;
  std::ifstream file(filename);
  std::string line;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::vector<int> lineInts;
      std::istringstream iss(line);
      int num;

      // parse numbers on each line
      while (iss >> num) {
        lineInts.push_back(num);
      }

      result.push_back(lineInts);
    }
  }
  return result;
}

std::vector<std::vector<int>>
computeDifferences(const std::vector<std::vector<int>> &input) {
  std::vector<std::vector<int>> differences;

  for (const auto &vec : input) {
    std::vector<int> vecDifferences;
    for (size_t i = 1; i < vec.size(); ++i) {
      vecDifferences.push_back(vec[i] - vec[i - 1]);
    }
    differences.push_back(vecDifferences);
  }

  return differences;
}

bool checkDifferenceConditions(const std::vector<int> &differences) {
  if (differences.empty())
    return false;

  // Check if all differences have the same sign
  bool allPositive = std::all_of(differences.begin(), differences.end(),
                                 [](int diff) { return diff > 0; });
  bool allNegative = std::all_of(differences.begin(), differences.end(),
                                 [](int diff) { return diff < 0; });

  if (!(allPositive || allNegative))
    return false;

  // Check if all differences are 1 or 2 apart
  return std::all_of(differences.begin(), differences.end(),
                     [](int diff) { return std::abs(diff) <= 3; });
}

int main() {
  std::vector<std::vector<int>> reports = readReports("input_day2.txt");

  std::vector<std::vector<int>> differences = computeDifferences(reports);

  int count = 0;
  for (const auto &vec : reports) {
    std::vector<int> differences;
    for (size_t i = 1; i < vec.size(); ++i) {
      differences.push_back(vec[i] - vec[i - 1]);
    }

    if (checkDifferenceConditions(differences)) {
      count++;
    }
  }

  std::cout << "Number of vectors fulfilling the conditions: " << count
            << std::endl;

  return 0;

  // for (const auto &vec : reports) {
  //   std::vector<int> differences;
  //   for (size_t i = 1; i < vec.size(); ++i) {
  //     differences.push_back(vec[i] - vec[i - 1]);
  //   }
  //
  //   bool meetsConditions = checkDifferenceConditions(differences);
  //
  //   // Print the vector and whether it meets the conditions
  //   for (int num : vec) {
  //     std::cout << num << " ";
  //   }
  //   std::cout << "- Meets conditions: " << (meetsConditions ? "Yes" : "No")
  //             << std::endl;
  // Print the parsed numbers to verify
  // for (size_t i = 0; i < 2 && i < reports.size(); ++i) {
  //   for (int num : reports[i]) {
  //     std::cout << num << " ";
  //   }
  //   std::cout << std::endl;
  // }
  //
}
