#ifndef UTILS_H
#define UTILS_H

#include "../element/element.h"

Element CalculatesGravityCenter(const std::vector<Element>& elements, const int dimensions);

Element MostDistantElement(const std::vector<Element>& elements, const Element& gravityCenter);

double EuclideanDistance(const Element& element1, const Element& element2);

#endif

