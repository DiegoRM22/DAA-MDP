#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <regex>


#include "problem.h"

double ConvertsToDouble(const std::string& str) {
  char* end;
  double value = strtod(str.c_str(), &end);
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
  for (int i = 0; i < elementsSize_; i++) {
    double* coordinates = new double[elementDimensions_];
    std::string line;
    std::getline(file, line);
    #include <regex>

    // Dentro del bucle while:
    while (line.empty() || std::regex_match(line, std::regex("^\\s*$"))) {
      std::getline(file, line);
    }

    // cambiar las ',' por '.'
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ',') {
        line[i] = '.';
      }
    }
    for (int j = 0; j < elementDimensions_; j++) {
      std::string value = line.substr(0, line.find(" "));
      line = line.substr(line.find(" ") + 1);
      coordinates[j] = ConvertsToDouble(value);
    }
    Element element(elementDimensions_, coordinates);
    elements_.push_back(element);
  }
}

void Problem::RemoveElement(const Element& element) {
  for (int i = 0; i < elementsSize_; i++) {
    if (elements_[i] == element) {
      elements_.erase(elements_.begin() + i);
      elementsSize_--;
      return;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Problem& problem) {
  os << "Problem with " << problem.GetElementsSize() << " elements and " << problem.GetElementDimensions() << " dimensions" << std::endl;
  for (const Element& element : problem.GetElements()) {
    os << element << std::endl;
  }
  return os;
}