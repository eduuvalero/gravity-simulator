#pragma once

#include <string>
#include <vector>

#include "engine/Body.h"

class CSVImporter{
    public:
        static std::vector<Body> import(const std::string& path);
    private:
        static std::vector<std::string> split(const std::string& line, char delimiter);
        static Body parseBody(const std::vector<std::string>& fields);
        static BodyType parseType(const std::string& type);
        static double parseDouble(const std::string& value);
        static std::string trim(const std::string& str);
};