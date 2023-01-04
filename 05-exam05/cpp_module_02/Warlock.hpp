#pragma once

#include "ASpell.hpp"
#include "SpellBook.hpp"
#include <iostream>
#include <map>
#include <string>

class Warlock {
private:
  std::string _name;
  std::string _title;
  SpellBook _spellBook;

public:
  Warlock(std::string name, std::string title) : _name(name), _title(title) {
    std::cout << _name << ": This looks like another boring day." << std::endl;
  }
  ~Warlock() { std::cout << _name << ": My job here is done!" << std::endl; }

  void introduce() {
    std::cout << _name << ": I am " << _name << ", " << _title << "!"
              << std::endl;
  }
  const std::string &getName() const { return _name; }
  const std::string &getTitle() const { return _title; }
  void setTitle(const std::string &title) { _title = title; }

  void learnSpell(ASpell *spell) { _spellBook.learnSpell(spell); }
  void forgetSpell(std::string spellName) { _spellBook.forgetSpell(spellName); }
  void launchSpell(std::string spellName, ATarget &target) {
    ASpell *spell = _spellBook.createSpell(spellName);
    spell->launch(target);
    delete spell;
  }
};
