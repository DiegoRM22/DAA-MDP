#include "movement.h"

bool operator==(const Movement& movement1, const Movement& movement2) {
  return movement1.GetElement1() == movement2.GetElement1() && movement1.GetElement2() == movement2.GetElement2();
}