#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include <iostream>

#include "../element/element.h"


class Movement {
 public:
  Movement(Element element1, Element element2) : element1_(element1), element2_(element2) {}
  Element GetElement1() const { return element1_; }
  Element GetElement2() const { return element2_; }

 private:
  Element element1_;
  Element element2_;
};

bool operator==(const Movement& movement1, const Movement& movement2);

#endif