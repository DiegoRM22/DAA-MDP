#ifndef BRANCH_AND_BOUND_H
#define BRANCH_AND_BOUND_H

#include <vector>

#include "../node/node.h"
#include "../solution/solution.h"
#include "../problem/problem.h"
#include "../GRASP/GRASP.h"



class BranchAndBound {
 public:
  BranchAndBound(const Problem& problem, const int solutionSize) : problem_(problem), solutionSize_(solutionSize) {}
  Solution Solve();
  void CreateActiveNodes();
  void CreateActiveNodes(Node* node, int index);
  void PrintActiveNodes();
 private:
  double LB = 0.0;
  double UB = 0.0;
  std::vector<Node*> ActiveNodes;
  Problem problem_;
  int solutionSize_;
};

#endif // BRANCH_AND_BOUND_H