#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <iostream>

#include "../element/element.h"

class Problem {
 public:
  Problem(const std::string& filename);
  std::vector<Element> GetElements() const { return elements_; }
  int GetElementsSize() const { return elementsSize_; }
  Element GetElement(int index) const { return elements_[index]; }
  int GetElementDimensions() const { return elementDimensions_; }
  void RemoveElement(const Element& element);
  void SetElements(const std::vector<Element>& elements) { elements_ = elements; }
 private:
  std::vector<Element> elements_;
  int elementsSize_;
  int elementDimensions_;
};

std::ostream& operator<<(std::ostream& os, const Problem& problem);

#endif