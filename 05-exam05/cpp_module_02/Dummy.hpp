#pragma once

#include "ATarget.hpp"

class Dummy : public ATarget {
  Dummy() : ATarget("Target Practice Dummy") {}

  ATarget *clone() { return new Dummy(); }
};
