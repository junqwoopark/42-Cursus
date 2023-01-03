#pragma once

#include "ASpell.hpp"
#include <iostream>

class ASpell;

class ATarget {
private:
  std::string _type;

public:
  ATarget(const std::string &type) : _type(type) {}
  virtual ~ATarget() {}

  const std::string &getType() const { return _type; }

  virtual ATarget *clone() = 0;
  void getHitBySpell(const ASpell &spell) {
    std::cout << _type << " has been " << spell.getEffects() << "!"
              << std::endl;
  }
};

#include "ASpell.hpp"
