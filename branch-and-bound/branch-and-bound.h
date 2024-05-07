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
  Solution GetPartialSolution(Node* node);
  Solution GetSolutionFromLeafNode(Node* node);
  void PrintParents(Node* node);
  void AddNodeAndDescendantsToActiveNodes(Node* node);
  void ComputeLeafNodes();
  double ComputeDmax(const Solution& solution);
  double ComputeDmaxForElement(const Element& element, const int left);
  double ComputeDmin(const std::vector<Element>& elements);
  double ComputeDminForElement(const Element& element, const int left);
  std::vector<Element> GetSortedVertexes(Element element);
  std::vector<Element> GetUnselectedElements(const Solution& partialSolution);
  double CalculateZValue(const Element& element, const Solution& partialSolution);
  double CalculateUB23(const Solution& partialSolution);
  double CalculateUB23(const Solution& partialSolution, const Element& element);
  double CalculatesZ2(Solution partialSolution, Solution AddedSolution);
  double CalculatesZPrime(Solution partialSolution, Solution AddedSolution);
  double CalculateIUB(double z, Solution partialSolution);
  std::vector<Element> SelectVerticesWithMaxZValues(const Solution& partialSolution, int left);

 private:
  double LB = 0.0;
  double UB = 0.0;
  std::vector<Node*> ActiveNodes;
  Problem problem_;
  int solutionSize_;
};

#endif // BRANCH_AND_BOUND_H