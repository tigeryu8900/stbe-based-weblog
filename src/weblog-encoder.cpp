#include "weblog-encoder.h"

namespace weblog {


std::time_t Encoder::toUnixTime(const std::string& time) {
  std::cout << "Input time: " << time;
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

bool Encoder::encode(const std::string& input, const std::string& output) {
  inf_.open(input);
  ouf_.open(output);
  char buf[4096];
  std::string host;
  std::string timestamp;
  std::string request;
  int reply;
  int bytes;
  
  while (!inf_.eof()) {
    inf_.getline(buf, 4096);
    re2::RE2::FullMatch(buf, re_, &host, &timestamp, &request, &reply, &bytes);
    ouf_ << "Host: " << host << " Timestamp (original): " << timestamp
          << " Timestamp(Unix): " << toUnixTime(timestamp) << " Request: " << request
          << " Reply: " << reply << " Bytes: " << bytes << std::endl;
  }
  return true;
}


} // weblog
