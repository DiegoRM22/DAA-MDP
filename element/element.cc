
#include <iostream>
#include <vector>

#include "element.h"

Element::Element(int dimensions, double* coordinates) {
  dimensions_ = dimensions;
  coordinates_ = new double[dimensions];
  for (int i = 0; i < dimensions; i++) {
    coordinates_[i] = coordinates[i];
  }
}

Element::Element(int dimensions, std::vector<double> coordinates) {
  dimensions_ = dimensions;
  coordinates_ = new double[dimensions];
  for (int i = 0; i < dimensions; i++) {
    coordinates_[i] = coordinates[i];
  }
}

std::ostream& operator<<(std::ostream& os, const Element& element) {
  double* coordinates = element.GetCoordinates();
  os << "(";
  for (int i = 0; i < element.GetDimensions(); i++) {
    os << coordinates[i] << (i == element.GetDimensions() - 1 ? "" : ", ");
  }
  os << ")";
  return os;
}

bool operator==(const Element& element1, const Element& element2) {
  if (element1.GetDimensions() != element2.GetDimensions()) {
    return false;
  }
  double* coordinates1 = element1.GetCoordinates();
  double* coordinates2 = element2.GetCoordinates();
  for (int i = 0; i < element1.GetDimensions(); i++) {
    if (coordinates1[i] != coordinates2[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const Element& element1, const Element& element2) {
  return !(element1 == element2);
}