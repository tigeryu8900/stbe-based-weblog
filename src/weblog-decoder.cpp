#include <cstdio>

#include <string>
#include <fstream>
#include <ctime>
#include "stbe.h"

#include "weblog-decoder.h"
#include "weblog-record.h"


namespace weblog {

namespace {

const char* month2String(int mon) {
  switch (mon) {
    case 0: return "Jan";
    case 1: return "Feb";
    case 2: return "Mar";
    case 3: return "Apr";
    case 4: return "May";
    case 5: return "Jun";
    case 6: return "Jul";
    case 7: return "Aug";
    case 8: return "Sep";
    case 9: return "Oct";
    case 10: return "Nov";
    case 11: return "Dec";
  }
  return "";
}

}  // namespace

bool Decoder::decode(const std::string& input_fname, const std::string& output_fname, const std::string& zone_str) {
  std::FILE* outf = fopen(output_fname.data(), "w");
  int zone = std::stoi(zone_str.substr(1, 2)) * 60 * 60 + std::stoi(zone_str.substr(3, 2)) * 60;
  if (zone_str[0] == '-') zone *= -1;
  std::cout << "input_fname: " << input_fname << std::endl;

  Record r;
  std::string line;
  std::string str_timestamp;

  stbe::Decoder<Record, WeblogRecordMarshaller> decoder(input_fname);
  while (decoder.nextRecord(r)) {
    std::time_t t = static_cast<std::time_t>(r.timestamp + zone);
    std::tm* tm = std::gmtime(&t);
    std::fprintf(outf, "%s - - [%02d/%s/%04d:%02d:%02d:%02d %s] \"%s\" %d ",
        r.host.data(), tm->tm_mday, month2String(tm->tm_mon), tm->tm_year + 1900, tm->tm_hour,
        tm->tm_min, tm->tm_sec, zone_str.data(), r.request.data(), r.reply);
    if (r.bytes != -1) {
      std::fprintf(outf, "%d\n", r.bytes);
    } else {
      std::fprintf(outf, "-\n");
    }
  }
  return true;
}

}  // namespace weblog
