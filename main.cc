
#include "problem/problem.h"
#include "element/element.h"
#include "utils/utils.h"
#include "greedy/greedy.h"
#include "solution/solution.h"
#include "local-search/local-search.h"
#include "local-search/swap-elements-search/swap-elements-search.h"
#include "GRASP/GRASP.h"
#include "tabu-search/tabu-search.h"
#include "branch-and-bound/branch-and-bound.h"

int main(int argc, char *argv[]) {
  srand(time(NULL));
  const std::string filename = argv[1];
  Problem problem(filename);
  std::vector<Element> elements = problem.GetElements();
  Element gravityCenter = CalculatesGravityCenter(elements, problem.GetElementDimensions());
  Element mostDistantElement = MostDistantElement(elements, gravityCenter);

  Greedy greedy(problem, 3);
  Solution solution = greedy.Solve();
  std::cout << "Solution: " << solution << std::endl;
  double distance = solution.CalculatesObjectiveFunction(problem);
  std::cout << "Objective function: " << distance << std::endl;
  std::vector<bool> inSolution = solution.GetInSolution();
  for (int i = 0; i < inSolution.size(); i++) {
    std::cout << inSolution[i] << " ";
  }
  std::cout << std::endl;

  SwapElementsSearch swapElementsSearch(problem, solution);
  Solution localSeacrch = swapElementsSearch.Solve();
  std::cout << "Local search: " << localSeacrch << std::endl;
  distance = localSeacrch.CalculatesObjectiveFunction(problem);
  std::cout << "Objective function: " << distance << std::endl;

  std::cout << "GRASP" << std::endl;

  GRASP grasp(problem, 3);
  Solution graspSolution = grasp.Solve();
  std::cout << "Solution: " << graspSolution << std::endl;
  distance = graspSolution.CalculatesObjectiveFunction(problem);
  std::cout << "Objective function: " << distance << std::endl;

  std::cout << "Tabu search" << std::endl;
  TabuSearch tabuSearch(problem, 1, 25);
  Solution tabuSolution = tabuSearch.Solve(graspSolution);
  std::cout << "Solution: " << tabuSolution << std::endl;
  distance = tabuSolution.CalculatesObjectiveFunction(problem);
  std::cout << "Objective function: " << distance << std::endl;

  std::cout << "\n\n\nBranch and bound" << std::endl;
  BranchAndBound branchAndBound(problem, 3);
  branchAndBound.CreateActiveNodes();
  branchAndBound.Solve();
  // branchAndBound.PrintActiveNodes();

  
  return 0;
}