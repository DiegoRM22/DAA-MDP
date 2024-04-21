#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <iostream>

#include "../element/element.h"
#include "../problem/problem.h"
#include "../utils/utils.h"
#include "../solution/solution.h"

class Greedy {
 public:
  Greedy(const Problem& problem, const int solutionSize) : problem_(problem), solutionSize_(solutionSize) {}
  Solution Solve();
 private:
  Problem problem_;
  int solutionSize_;
};

#endif