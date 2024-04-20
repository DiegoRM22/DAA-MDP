#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>


class Element {
 public:
  Element(int dimensions, double* coordinates);
  int GetDimensions() const { return dimensions_; }
  double* GetCoordinates() const { return coordinates_; }
 private:
  int dimensions_;
  double* coordinates_;
};

// Ostream operator overload for Element
std::ostream& operator<<(std::ostream& os, const Element& element);

#endif