#ifndef JSON_H
#define JSON_H

#include "json.hpp"

#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>

using namespace std;

using json = nlohmann::json;


inline ifstream temp("/Users/ericyang/Desktop/goytris/droydfent/Template/src/defaultdata.json");

inline json D{json::parse(temp)};



#endif 