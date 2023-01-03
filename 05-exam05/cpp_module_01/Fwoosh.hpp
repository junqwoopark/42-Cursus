#pragma once

#include "ASpell.hpp"

class Fwoosh : public ASpell {
  Fwoosh() : ASpell("Fwoosh", "fwooshed") {}

  ASpell *clone() { return new Fwoosh(); }
};
