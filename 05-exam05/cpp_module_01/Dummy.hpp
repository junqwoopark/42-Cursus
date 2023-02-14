#pragma once

#include "ATarget.hpp"

class Dummy : public ATarget {
public:
  Dummy() : ATarget("Target Practice Dummy") {}

  ATarget *clone() { return new Dummy(); }
};
