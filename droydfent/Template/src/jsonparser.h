#ifndef JSON_H
#define JSON_H

#include "json.hpp"

#include <fstream>
#include <string>
#include <streambuf>

using namespace std;

using json = nlohmann::json;


inline ifstream temp("defaultdata.json");
inline string rawdata((istreambuf_iterator<char>(temp)),
                 istreambuf_iterator<char>());
inline json D{json::parse(rawdata)};

#endif 