#pragma once

#include "ASpell.hpp"

class Fireball : public ASpell {
  Fireball() : ASpell("Fireball", "burnt to a crisp") {}

  ASpell *clone() { return new Fireball(); }
};
