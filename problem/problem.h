#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <iostream>

#include "../element/element.h"

class Problem {
 public:
  Problem(const std::string& filename);
  std::vector<Element> GetElements() const { return elements_; }
 private:
  std::vector<Element> elements_;
  int elementsSize_;
  int elementDimensions_;
};

#endif