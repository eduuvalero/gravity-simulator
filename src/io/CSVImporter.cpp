#include "io/CSVImporter.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

std::vector<Body> CSVImporter::import(const std::string& path){
    std::ifstream file(path);
    std::vector<Body>  bodies;
    std::string line;

    if(!file.is_open()){
        throw std::runtime_error("Couldn't open CSV file: " + path);
    }

    getline(file, line);

    while(getline(file, line)){
        std::vector<std::string> fields = split(line, ',');
        bodies.push_back(parseBody(fields));
    }

    return bodies;
};

std::vector<std::string> CSVImporter::split(const std::string& line, char delimiter){
    std::vector<std::string> fields(13, "0");
    std::stringstream ss(line);
    std::string field;

    while( getline(ss, field, delimiter) ){
        fields.push_back(trim(field));
    }

    return fields;
}

Body CSVImporter::parseBody(const std::vector<std::string>& fields){
    Body body;

    body.name = fields[0];
    body.type = parseType(fields[1]);
    body.mass = parseDouble(fields[2]);
    body.radius = parseDouble(fields[3]);

    body.position.x = parseDouble(fields[4]);
    body.position.y  = parseDouble(fields[5]);
    body.position.z  = parseDouble(fields[6]);

    body.velocity.x = parseDouble(fields[7]);
    body.velocity.y = parseDouble(fields[8]);
    body.velocity.z = parseDouble(fields[9]);

    body.color.x = parseFloat(fields[10]);
    body.color.y = parseFloat(fields[11]);
    body.color.z = parseFloat(fields[12]);

    return body;
}

BodyType CSVImporter::parseType(const std::string& type){
    std::string lower = type;

    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); } );

    if (lower == "star"){
        return BodyType::Star;
    }

    if (lower == "planet"){
        return BodyType::Planet;
    }

    throw std::runtime_error("Unknown body type: " + type);
}

double CSVImporter::parseDouble(const std::string& value){
    std::size_t pos = 0;

    double result = std::stod(value, &pos);

    if (pos != value.size()){
        throw std::runtime_error("Invalid number: " + value);
    }

    return result;
}

double CSVImporter::parseFloat(const std::string& value){
    std::size_t pos = 0;

    double result = std::stof(value, &pos);

    if (pos != value.size()){
        throw std::runtime_error("Invalid number: " + value);
    }

    return result;
}

std::string CSVImporter::trim(const std::string& str){
    const auto first = str.find_first_not_of(" \t\n\r\f\v");

    if (first == std::string::npos){
        return "";
    }

    const auto last = str.find_last_not_of(" \t\n\r\f\v");

    return str.substr(first, last - first + 1);
}