#pragma once

#include "ASpell.hpp"

class Fwoosh : public ASpell {
public:
  Fwoosh() : ASpell("Fwoosh", "fwooshed") {}

  ASpell *clone() { return new Fwoosh(); }
};
