//
// Created by Joca on 02/04/2023.
//
#include "Station.h"

Station::Station(std::string name, std::string district, std::string municipality, std::string township, std::string line):
name(name),district(district),municipality(municipality),township(township),line(line){
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}
Station::Station(std::string name) : name(name){
    this->name = name;
}
Station::Station(){
}
std::string Station::getName() const{
    return this->name;
}
std::string Station::getDistrict() const {
    return this->district;
}
std::string Station::getLine() const {
    return this->line;
}
std::string Station::getMunicipality() const {
    return this->municipality;
}
std::string Station::getTownship() const {
    return this->township;
}
bool Station::operator==(const Station& station) const{
    return this->name==station.name;
}
