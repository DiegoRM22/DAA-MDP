

#include "element.h"

Element::Element(int dimensions, double* coordinates) {
  dimensions_ = dimensions;
  coordinates_ = new double[dimensions];
  for (int i = 0; i < dimensions; i++) {
    coordinates_[i] = coordinates[i];
  }
}

std::ostream& operator<<(std::ostream& os, const Element& element) {
  os << "Element with dimensions: " << element.GetDimensions() << " and coordinates: ";
  double* coordinates = element.GetCoordinates();
  for (int i = 0; i < element.GetDimensions(); i++) {
    os << coordinates[i] << " ";
  }
  return os;
}