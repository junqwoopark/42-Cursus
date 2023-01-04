#pragma once

#include "ASpell.hpp"

class Polymorph : public ASpell {
  Polymorph() : ASpell("Polymorph", "turned into a critter") {}

  ASpell *clone() { return new Polymorph(); }
};
