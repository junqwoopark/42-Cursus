#pragma once

#include <iostream>

class ASpell;

class ATarget {
private:
  std::string _type;

public:
  ATarget(const std::string &type) : _type(type) {}
  virtual ~ATarget() {}

  const std::string &getType() const { return _type; }

  virtual ATarget *clone() const = 0;
  void getHitBySpell(const ASpell &spell) const;
};

#include "ASpell.hpp"
