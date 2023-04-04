//
// Created by Joca on 02/04/2023.
//

#ifndef FIRSTDA_READFILES_H
#define FIRSTDA_READFILES_H

#include <memory>
#include <list>
#include <vector>
#include "Station.h"

struct StationNode;

enum ServicesOfTrip{
    STANDARD,
    ALFA_PENDULAR
};

struct Trip{
    Trip(int id,std::shared_ptr<StationNode> StationPartida, std::shared_ptr<StationNode> DestinyStation,enum ServicesOfTrip Service,int Capacity,int ActualFlow);

    std::shared_ptr<StationNode> DestinyStation;

    std::shared_ptr<StationNode> StationPartida;

    int id;

    enum ServicesOfTrip Service;

    int Capacity;

    int ActualFlow;
};

struct StationNode{
    StationNode(Station station);

    Station station;

    bool visited;

    int dist;

    std::vector<int> tripsid;

    std::shared_ptr<StationNode> parent;

    std::shared_ptr<StationNode> prev;

    bool operator==(const StationNode& node) const;


};

class ReadFiles{
    public:
    ReadFiles(ReadFiles& other) = delete;

    void loadFiles();

    void operator=(const ReadFiles&) = delete;

    static ReadFiles* getInstance();

    bool addTrip(int i,std::string StationPreviously,std::string StationDestiny,enum ServicesOfTrip Service,int Capacity,int ActualFlow=0);

    std::shared_ptr<StationNode> getStationNode(std::string nameofstation);

    void resetdistanceStations();

    void resetVisitedStations();

    void resetActualFlow();

    private:
    std::vector<std::shared_ptr<StationNode>> Stations;
    std::vector<std::shared_ptr<Trip>> trips;
    ReadFiles(){}

    static ReadFiles* instance;

};

#endif //FIRSTDA_READFILES_H
