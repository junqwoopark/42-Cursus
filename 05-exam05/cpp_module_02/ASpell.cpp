#include "ASpell.hpp"

void ASpell::launch(const ATarget &target) const {
  target.getHitBySpell(*this);
}
