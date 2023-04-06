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
enum FlowType{
    NOT_DEFINED,
    FROM_DEPARTURE_TO_ARRIVAL,
    FROM_ARRIVAL_TO_DEPARTURE
};
struct Trip{
    Trip(int id,std::shared_ptr<StationNode> StationPartida, std::shared_ptr<StationNode> DestinyStation,enum ServicesOfTrip Service,int Capacity,int ActualFlow,enum FlowType flowType);

    std::shared_ptr<StationNode> DestinyStation;

    std::shared_ptr<StationNode> StationPartida;

    int id;

    enum ServicesOfTrip Service;

    int Capacity;

    int ActualFlow;

    enum FlowType flowTypee;
};

struct StationNode{
    StationNode(Station station);

    Station station;

    bool visited;

    int idTOBFS;

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

    void resetVisitedStations();

    void resetActualFlow();

    std::vector<std::shared_ptr<Trip>> gettrips();

    void setActualFlow(int idOfTrip,int value);

    void setFlowTypee(int idOfTrip,FlowType type);

private:
    std::vector<std::shared_ptr<StationNode>> Stations;
    std::vector<std::shared_ptr<Trip>> trips;
    ReadFiles(){}

    static ReadFiles* instance;

};

#endif //FIRSTDA_READFILES_H
