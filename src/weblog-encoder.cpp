#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "stbe.h"
#include "weblog-record.h"

#include "weblog-encoder.h"

namespace weblog {

std::time_t Encoder::toUnixTime(const std::string& time) {
  int day;
  std::string mon_str;
  int yr;
  int hr;
  int min;
  int sec;
  std::string zone_str;
  re2::RE2::FullMatch(time, timestamp_re_, &day, &mon_str, &yr, &hr, &min, &sec, &zone_str);
  int mon;
  if (mon_str == "Jan") {
    mon = 0;
  } else if (mon_str == "Feb") {
    mon = 1;
  } else if (mon_str == "Mar") {
    mon = 2;
  } else if (mon_str == "Apr") {
    mon = 3;
  } else if (mon_str == "May") {
    mon = 4;
  } else if (mon_str == "Jun") {
    mon = 5;
  } else if (mon_str == "Jul") {
    mon = 6;
  } else if (mon_str == "Aug") {
    mon = 7;
  } else if (mon_str == "Sep") {
    mon = 8;
  } else if (mon_str == "Oct") {
    mon = 9;
  } else if (mon_str == "Nov") {
    mon = 10;
  } else if (mon_str == "Dec") {
    mon = 11;
  } else {
    mon = -1;
    std::cout << "The month \"" << mon_str << "\" is not recognized." << std::endl;
  }
  int zone = std::stoi(zone_str.substr(1, 2)) * 60 * 60 + std::stoi(zone_str.substr(3, 2)) * 60;
  if (zone_str[0] == '-') {
    zone *= -1;
  }
  std::tm tm;
  tm.tm_mday = day;
  tm.tm_mon = mon;
  tm.tm_year = yr - 1900;
  tm.tm_hour = hr;
  tm.tm_min = min;
  tm.tm_sec = sec;
  return static_cast<time_t>(std::mktime(&tm) - zone);
}

bool Encoder::encode(const std::string& input_fname, const std::string& output_fname) {
  if (!re_.ok() || !timestamp_re_.ok()) {
    std::cout << "in valid regular expression" << std::endl;
    return false;
  }

  std::ifstream inf(input_fname);

  Record record;
  std::string line;
  std::string str_timestamp;
  std::string str_bytes;

  // mktime uses local timezone, we need to set TZ to "" to let system use UTC
  char* tz = getenv("TZ");
  setenv("TZ", "", 1);
  tzset();

  stbe::Builder<Record, WeblogRecordMarshaller> builder;
  builder.initialize(output_fname);
  while (std::getline(inf, line)) {
    bool success = re2::RE2::FullMatch(line, re_, &record.host, &str_timestamp, &record.request, &record.reply, &str_bytes);
    if (!success) {
      std::cout << "unrecognized record:" << std::endl << line << std::endl;
    }
    record.timestamp = toUnixTime(str_timestamp);
    if (str_bytes == "-") {
      record.bytes = -1;
    } else {
      record.bytes = std::stoi(str_bytes);
    }
    builder.add(record);
  }
  builder.finalize();

  // restore TZ
  if (tz) {
    setenv("TZ", tz, 1);
  } else {
    unsetenv("TZ");
  }
  tzset();
  return true;
}


}  // namespace weblog
