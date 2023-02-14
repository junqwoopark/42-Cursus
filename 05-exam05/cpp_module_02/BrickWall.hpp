#pragma once

#include "ATarget.hpp"

class BrickWall : public ATarget {
public:
  BrickWall() : ATarget("Inconspicuous Red-brick Wall") {}
  ATarget *clone() const { return new BrickWall(); }
};
