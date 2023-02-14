#pragma once

#include <iostream>

class ATarget;

class ASpell {
private:
  std::string _name;
  std::string _effects;

public:
  ASpell(const std::string &name, const std::string &effects)
      : _name(name), _effects(effects) {}
  virtual ~ASpell() {}

  std::string getName() const { return _name; }
  std::string getEffects() const { return _effects; }

  virtual ASpell *clone() = 0;

  void launch(const ATarget &target);
};

#include "ATarget.hpp"
