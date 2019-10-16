#include <string>

#include "strutil.h"

bool starts_with(const std::string & s, const std::string & prefix) {
  if (s.size() < prefix.size()) return false;
  return s.substr(0, prefix.size()) == prefix;
}

const std::string trim_prefix(const std::string & s, const std::string & prefix) {
  return s.substr(prefix.size());
}

