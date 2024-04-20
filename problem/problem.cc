#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>


#include "problem.h"

double ConvertsToDouble(const std::string& str) {
  char* end;
  double value = strtod(str.c_str(), &end);
  if (*end != '\0') {
    std::cerr << "Error: could not convert string to double" << std::endl;
    exit(1);
  }
  return value;
}

Problem::Problem(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: could not open file " << filename << std::endl;
    exit(1);
  }
  // first line of file contains the number of elements
  file >> elementsSize_;
  // second line of file contains the number of dimensions
  file >> elementDimensions_;
  std::cout << "Elements size: " << elementsSize_ << std::endl;
  std::cout << "Element dimensions: " << elementDimensions_ << std::endl;
  for (int i = 0; i < elementsSize_; i++) {
    double* coordinates = new double[elementDimensions_];
    std::string line;
    std::getline(file, line);
    while (line.empty()) {
      std::getline(file, line);
    }
    // cambiar las ',' por '.'
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ',') {
        line[i] = '.';
      }
    }
    std::cout << line << std::endl;
    for (int j = 0; j < elementDimensions_; j++) {
      std::string value = line.substr(0, line.find(" "));
      line = line.substr(line.find(" ") + 1);
      std::cout << value << std::endl;
      coordinates[j] = ConvertsToDouble(value);
    }
    Element element(elementDimensions_, coordinates);
    elements_.push_back(element);
  }
}