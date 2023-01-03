#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include "ASpell.hpp"
#include "ATarget.hpp"
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Warlock {
private:
  string _name;
  string _title;
  std::map<std::string, ASpell *> _spells;

public:
  Warlock(string name, string title) : _name(name), _title(title) {
    cout << _name << ": This looks like another boring day." << endl;
  }
  ~Warlock() { cout << _name << ": My job here is done!" << endl; }

  void introduce() {
    cout << _name << ": I am " << _name << ", " << _title << "!" << endl;
  }
  const string &getName() const { return _name; }
  const string &getTitle() const { return _title; }
  void setTitle(const string &title) { _title = title; }

  void learnSpell(ASpell *spell) { _spells[spell->getName()] = spell; }
  void forgetSpell(std::string spellName) { _spells[spellName] = NULL; }
  void launchSpell(std::string spellName, ATarget &target) {
    if (_spells[spellName])
      _spells[spellName]->launch(target);
  }
};

#endif
