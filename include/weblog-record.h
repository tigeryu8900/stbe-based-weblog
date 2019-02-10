#pragma once

#include <string>

#include "stbe.h"

namespace weblog {

// Record data type to be stored in stbe.
struct Record {
  std::string host;
  uint32_t timestamp;
  std::string request;
  uint32_t reply;
  uint32_t bytes;
};

/*// for EXPECT_EQ.
bool operator==(const Record& l, const Record& r) {
  return l.host == r.host &&
         l.timestamp == r.timestamp &&
         l.request == r.request &&
         l.reply == r.reply &&
         l.bytes == r.bytes;
}*/
// Marshaller for our own data type: Record.
class WeblogRecordMarshaller {
public:
  static float avgSize() {
    return stbe::kAvgVarintSize * 5;  // stores 5 varints per record
  }
  static void add2Trie(stbe::TrieValueEncoder& encoder, const Record& r) {
    encoder.addString2Trie(r.host);
    encoder.addString2Trie(r.request);
  }
  static void encode(stbe::TrieValueEncoder& encoder, const Record& r) {
    encoder.encodeString(0);
    encoder.encodeUint32(static_cast<uint32_t>(r.timestamp));
    encoder.encodeString(1);
    encoder.encodeUint32(r.reply);
    encoder.encodeUint32(r.bytes);
  }

  static bool decode(stbe::TrieValueDecoder& decoder, Record& r) {
    bool res = decoder.decodeString(r.host);
    res &= decoder.decodeUint32(r.timestamp);
    res &= decoder.decodeString(r.request);
    res &= decoder.decodeUint32(r.reply);
    res &= decoder.decodeUint32(r.bytes);
    return res;
  }
  static bool skip(stbe::TrieValueDecoder& decoder) {
    bool res = decoder.skipString();
    res &= decoder.skipUint32();
    res &= decoder.skipString();
    res &= decoder.skipUint32();
    res &= decoder.skipUint32();
    return res;
  }
};

} // namespace weblog
