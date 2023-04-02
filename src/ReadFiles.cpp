#include <fstream>
#include <sstream>
#include "ReadFiles.h"
#include <algorithm>

ReadFiles* ReadFiles::instance = nullptr;


std::string& trim_string(std::string& str) {
#ifndef _WIN32
    /*
            O windows usa \r\n para sinalizar o fim de uma linha, Enquanto que o linux só usa \n.
            Ou seja ao ler ficheiros com o formato do windows no linux vamos ter um caracter a mais
            e vai induzir em erros na comparação de turmas.
        */
        if(str.find_first_of('\r') != std::string::npos)
            str = str.substr(0, str.size()-1);
#endif
    return str;
}

void ReadFiles::loadFiles(){
    //o windows usa \\ para os diretórios enquanto o unix usa /
#ifndef _WIN32
    std::ifstream file_stations = std::ifstream("../docs/stations.csv");
    std::ifstream file_trips = std::ifstream("../docs/network.csv");
#else
    std::ifstream file_stations = std::ifstream("..\\docs\\stations.csv");
    std::ifstream file_trips = std::ifstream("..\\docs\\network.csv");
#endif

    std::string buffer;
    //skip first line
    std::getline(file_stations, buffer);
    while(std::getline(file_stations, buffer).good()){
        std::istringstream line(buffer);

        std::string name;
        std::getline(line, name, ',');
        std::string district;
        std::getline(line, district, ',');
        std::string municipality;
        std::getline(line, municipality, ',');
        std::string township;
        std::getline(line, township, ',');
        std::string linestation;
        std::getline(line,linestation,',');
        linestation = trim_string(linestation);

        auto station = Station(name,district,municipality,township,linestation);

        Stations.push_back(std::make_shared<StationNode>(station));
    }

    std::getline(file_trips, buffer);
    while(std::getline(file_trips, buffer).good()){
        std::istringstream line(buffer);

        std::string stationorigin;
        std::getline(line, stationorigin, ',');
        std::string stationdestiny;
        std::getline(line, stationdestiny, ',');
        std::string capacity;
        std::getline(line, capacity, ',');
        std::string service;
        std::getline(line, service, ',');

        service = trim_string(service);

        ServicesOfTrip servicesOfTrip;

        if(service=="STANDART"){
            servicesOfTrip = STANDARD;
        }
        else{
            servicesOfTrip = ALFA_PENDULAR;
        }

        addTrip(stationorigin,stationdestiny,servicesOfTrip,std::stoi(capacity));
    }
}

bool ReadFiles::addTrip(std::string StationPreviously,std::string StationDestiny,enum ServicesOfTrip Service,int Capacity,int ActualFlow){
    std::shared_ptr<StationNode> src = getStationNode(StationPreviously);
    if(src.get()== nullptr) return false;
    std::shared_ptr<StationNode> dst = getStationNode(StationDestiny);
    if(dst.get()== nullptr) return false;

    bool found = false;

    for(auto it = src->trip.begin();it!=src->trip.end();it++){
        if((*(*it).DestinyStation)==*dst){
            found = true;
            return false;
        }
    }
    auto tripnew = Trip(dst,Service,Capacity,ActualFlow);
    src->trip.push_back(tripnew);
    return found;
}

std::shared_ptr<StationNode> ReadFiles::getStationNode(std::string nameofstation){
    return *std::find(Stations.begin(),Stations.end(),std::make_shared<StationNode>(Station(nameofstation)));
}
void ReadFiles::resetdistanceStations() {
    static const std::shared_ptr<StationNode> null = std::shared_ptr<StationNode>(nullptr);
    for (auto it = Stations.begin(); it != Stations.end(); it++) {
        (*it)->dist = -1;
    }
}

void ReadFiles::resetVisitedStations() {
    static const std::shared_ptr<StationNode> null =std::shared_ptr<StationNode>(nullptr);
    for(auto it = Stations.begin(); it != Stations.end(); it++){
        (*it)->visited = false;
        (*it)->prev = null;
        (*it)->dist = -1;
    }
}
Trip::Trip(std::shared_ptr<StationNode> DestinyStation,enum ServicesOfTrip Service,int Capacity,int ActualFlow){
    this->DestinyStation=DestinyStation;
    this->Service=Service;
    this->Capacity=Capacity;
    this->ActualFlow=ActualFlow;
}

StationNode::StationNode(Station station1){
    this->station=station1;
    this->visited=false;
}

bool StationNode::operator==(const StationNode& node) const{
    return station == node.station;
}
ReadFiles* ReadFiles::getInstance(){
    if(instance == nullptr) instance = new ReadFiles();

    return instance;
}