#pragma once

#include <string>
#include "re2/re2.h"

namespace weblog {

class Encoder {
private:
  re2::RE2 re_;
  re2::RE2 timestamp_re_;
  std::time_t toUnixTime(const std::string& time);

public:
  Encoder() : re_("(\\S+) - - \\[([^\\]]+)\\] \"(.*)\" ([0-9]+) ([0-9,-]+)"),
              timestamp_re_("([0-9]+)/([A-z]+)/([0-9]+):([0-9]+):([0-9]+):([0-9]+) ([\\+-][0-9]+)") {
    
  }
  bool encode(const std::string& input, const std::string& output);
};


}  // namespace weblog
