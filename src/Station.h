//
// Created by Joca on 02/04/2023.
//

#include <string>

#ifndef FIRSTDA_STATION_H
class Station{
public:
    Station(std::string name, std::string district, std::string municipality, std::string township, std::string line);
    Station(std::string name);
    Station();
    std::string getName() const;
    std::string getDistrict() const;
    std::string getMunicipality() const;
    std::string getTownship() const;
    std::string getLine() const;
    bool operator==(const Station& station) const;

private:
    std::string name;
    std::string district;   //Distrito
    std::string municipality;   //Municipio
    std::string township;   //Freguesia
    std::string line;   //Linha Ex: Linha do Minho, Linha do Sul, etc...


};
#define FIRSTDA_STATION_H

#endif //FIRSTDA_STATION_H
