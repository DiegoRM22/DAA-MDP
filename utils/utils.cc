#include <iostream>
#include <vector>
#include <cmath>

#include "../element/element.h"
#include "utils.h"

/**
 * Calculates the gravity center of a set of elements.
*/
Element CalculatesGravityCenter(const std::vector<Element>& elements, const int dimensions) {
  std::vector<double> gravityCenter(dimensions, 0);
  for (int i = 0; i < dimensions; i++) {
    for (const Element& element : elements) {
      gravityCenter[i] += element.GetCoordinates()[i];
    }
    gravityCenter[i] /= elements.size();
  }
  return Element(dimensions, gravityCenter);
}

/**
 * Finds the element that is most distant from the gravity center
 * using the Euclidean distance.
*/
Element MostDistantElement(const std::vector<Element>& elements, const Element& gravityCenter) {
  Element mostDistantElement = elements[0];
  double maxDistance = EuclideanDistance(mostDistantElement, Element(gravityCenter.GetDimensions(), gravityCenter.GetCoordinates()));
  for (const Element& element : elements) {
    double distance = EuclideanDistance(element, Element(gravityCenter.GetDimensions(), gravityCenter.GetCoordinates()));
    if (distance > maxDistance) {
      maxDistance = distance;
      mostDistantElement = element;
    }
  }
  return mostDistantElement;
}

/**
 * Calculates the Euclidean distance between two elements.
*/
double EuclideanDistance(const Element& element1, const Element& element2) {
  double distance = 0;
  for (int i = 0; i < element1.GetDimensions(); i++) {
    distance += pow(element1.GetCoordinates()[i] - element2.GetCoordinates()[i], 2);
  }
  return sqrt(distance);
}