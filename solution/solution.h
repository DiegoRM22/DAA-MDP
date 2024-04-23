#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <iostream>

#include "../element/element.h"
#include "../problem/problem.h"
#include "../utils/utils.h"

class Solution {
 public:
  Solution() {}
  void AddElement(const Element& element) { elements.push_back(element); }
  int GetSize() const { return elements.size(); }
  std::vector<Element> GetElements() const { return elements; }
  void SetInSolution(const std::vector<Element>& problemElements);
  std::vector<bool> GetInSolution() const { return inSolution; }
  double CalculatesObjectiveFunction(const Problem& problem);
  void ReplaceElement(const Element& element, const int index) { elements[index] = element; }
 private:
  std::vector<Element> elements;
  std::vector<bool> inSolution;
};

std::ostream& operator<<(std::ostream& os, const Solution& solution);

#endif