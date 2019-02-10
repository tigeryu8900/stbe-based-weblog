#pragma once

#include <string>

namespace weblog {

class Decoder {
public:
  Decoder() {}
  bool decode(const std::string& input, const std::string& output, const std::string& zone = "-0400");
};

} // namespace weblog
