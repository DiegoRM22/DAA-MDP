
#include "problem/problem.h"
#include "element/element.h"

int main(int argc, char *argv[]) {
  const std::string filename = argv[1];
  Problem problem(filename);
  std::vector<Element> elements = problem.GetElements();
  for (const Element& element : elements) {
    std::cout << element << std::endl;
  }
  return 0;
}