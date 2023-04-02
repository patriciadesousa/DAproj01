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
    Trip(std::shared_ptr<StationNode> DestinyStation,enum ServicesOfTrip Service,int Capacity,int ActualFlow);

    std::shared_ptr<StationNode> DestinyStation;

    enum ServicesOfTrip Service;

    int Capacity;

    int ActualFlow;
};

struct StationNode{
    StationNode(Station station);

    Station station;

    bool visited;

    int dist;

    std::list<Trip> trip;

    std::shared_ptr<StationNode> parent;

    std::shared_ptr<StationNode> prev;

    bool operator==(const StationNode& node) const;


};

class ReadFiles{
    struct StationEquals{
        bool operator()(const std::shared_ptr<StationNode>& stationNode1, const std::shared_ptr<StationNode>& stationNode2);
    };
    public:
    ReadFiles(ReadFiles& other) = delete;

    void loadFiles();

    void operator=(const ReadFiles&) = delete;

    static ReadFiles* getInstance();

    bool addTrip(std::string StationPreviously,std::string StationDestiny,enum ServicesOfTrip Service,int Capacity,int ActualFlow=0);

    std::shared_ptr<StationNode> getStationNode(std::string nameofstation);

    void resetdistanceStations();

    void resetVisitedStations();

    private:
    std::vector<std::shared_ptr<StationNode>> Stations;
    ReadFiles(){}

    static ReadFiles* instance;

};

#endif //FIRSTDA_READFILES_H
