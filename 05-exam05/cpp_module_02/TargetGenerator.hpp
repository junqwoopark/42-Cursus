#pragma once

#include "ATarget.hpp"
#include <map>

class TargetGenerator {
  std::map<std::string, ATarget *> _targets;

public:
  TargetGenerator() {}
  ~TargetGenerator() {}

  void learnTargetType(ATarget *target) {
    _targets[target->getType()] = target;
  }
  void forgetTargetType(const std::string &target) { _targets.erase(target); }
  ATarget *createTarget(const std::string &target) {
    return _targets[target]->clone();
  }
};
