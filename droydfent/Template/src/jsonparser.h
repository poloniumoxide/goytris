#ifndef JSON_H
#define JSON_H

#include "json.hpp"

#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>
#include <raylib.h>

using namespace std;

using json = nlohmann::json;

inline ifstream temp(string(GetApplicationDirectory()).substr(0, string(GetApplicationDirectory()).size() - 4) + "src/defaultdata.json");

inline json D{json::parse(temp)};


#endif 