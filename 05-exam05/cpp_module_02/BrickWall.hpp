#pragma once

#include "ATarget.hpp"

class BrickWall : public ATarget {
  BrickWall() : ATarget("Inconspicuous Red-brick Wall") {}

  ATarget *clone() { return new BrickWall(); }
};
