#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <vector>


class Element {
 public:
  Element(int dimensions, double* coordinates);
  Element(int dimensions, std::vector<double> coordinates);

  int GetDimensions() const { return dimensions_; }
  double* GetCoordinates() const { return coordinates_; }
 private:
  int dimensions_;
  double* coordinates_;
};

// Ostream operator overload for Element
std::ostream& operator<<(std::ostream& os, const Element& element);
bool operator==(const Element& element1, const Element& element2);

#endif