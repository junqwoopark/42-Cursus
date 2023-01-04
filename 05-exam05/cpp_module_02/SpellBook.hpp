#pragma once

#include "ASpell.hpp"
#include <map>

class SpellBook {
  std::map<std::string, ASpell *> _spells;

public:
  SpellBook() {}
  ~SpellBook();

  void learnSpell(ASpell *spell) { _spells[spell->getName()] = spell; }
  void forgetSpell(const std::string &spellName) { _spells.erase(spellName); }
  ASpell *createSpell(const std::string &spellName) {
    return _spells[spellName]->clone();
  }
};
