
#include "problem/problem.h"
#include "element/element.h"
#include "utils/utils.h"
#include "greedy/greedy.h"
#include "solution/solution.h"
#include "local-search/local-search.h"
#include "local-search/swap-elements-search/swap-elements-search.h"

int main(int argc, char *argv[]) {
  const std::string filename = argv[1];
  Problem problem(filename);
  std::vector<Element> elements = problem.GetElements();
  std::cout << problem;
  Element gravityCenter = CalculatesGravityCenter(elements, problem.GetElementDimensions());
  std::cout << "Gravity center: " << gravityCenter << std::endl;
  Element mostDistantElement = MostDistantElement(elements, gravityCenter);
  std::cout << "Most distant element: " << mostDistantElement << std::endl;

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

  
  return 0;
}