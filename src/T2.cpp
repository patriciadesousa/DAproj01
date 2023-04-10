#include <queue>
#include <iostream>
#include "T2.h"
#include "map"
using namespace std;


bool T2::bfs(std::shared_ptr<StationNode> src, std::shared_ptr<StationNode> dst,ReadFiles * readFiles)
{
    readFiles->resetVisitedStations();
    std::queue<std::shared_ptr<StationNode>> q;
    q.push(src);
    src->visited = true;
    src->parent = nullptr;
    std::vector<std::shared_ptr<Trip>> trips = readFiles->gettrips();

    // Standard BFS Loop
    while (!q.empty()) {
        std::shared_ptr<StationNode> u = q.front();
        q.pop();

        for (auto it = u->tripsid.begin();it!=u->tripsid.end();it++) {
            std::shared_ptr<Trip> trip = trips[*it];
            std::shared_ptr<StationNode> visita;
            enum FlowType percurso;
            if(trip->DestinyStation==u){
                visita = trip->StationPartida;
                percurso = FROM_ARRIVAL_TO_DEPARTURE;
            }
            else{visita = trip->DestinyStation;percurso = FROM_DEPARTURE_TO_ARRIVAL;}
            if (!visita->visited && ((trip->flowTypee==NOT_DEFINED)||(trip->ActualFlow!=trip->Capacity && trip->flowTypee==percurso)||(trip->ActualFlow!=0 && trip->flowTypee!=percurso) )){
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // true

                if (visita == dst) {
                    visita->parent = u;
                    visita->idTOBFS=*it;
                    visita->visited=true;
                    return true;
                }
                q.push(visita);
                visita->parent = u;
                visita->visited = true;
                visita->idTOBFS=*it;
            }
        }
    }

    // We didn't reach sink in BFS starting from source, so
    // return false
    return false;
}
//2.1
int T2::MaxFlowNormal(std::string Partida,std::string Chegada){
    ReadFiles * readFiles = ReadFiles::getInstance();
    std::shared_ptr<StationNode> src = readFiles->getStationNode(Partida);
    if(src.get()== nullptr) return -1;
    std::shared_ptr<StationNode> dst = readFiles->getStationNode(Chegada);
    if(dst.get()== nullptr) return -1;
    readFiles->resetVisitedStations();
    readFiles->resetActualFlow();
    int max_flow = 0;
    std::shared_ptr<StationNode> v;
    std::shared_ptr<StationNode> u;
    while(T2::bfs(src,dst,readFiles)){
        std::vector<std::shared_ptr<Trip>> trips = readFiles->gettrips();
        std::vector<enum FlowType> path;
        int path_flow = INT_MAX;
        for(v=dst;v!=src;v=v->parent){
            std::shared_ptr<Trip> relation = trips[v->idTOBFS];
            if(relation->flowTypee==NOT_DEFINED) {
                if(relation->ActualFlow!=0){
                    std::cout<<v->station.getName()<<"\n";
                }
                enum FlowType typeofflow;
                if (relation->DestinyStation == v) {
                    typeofflow = FROM_DEPARTURE_TO_ARRIVAL;
                    readFiles->setFlowTypee(v->idTOBFS, typeofflow);
                } else {
                    typeofflow = FROM_ARRIVAL_TO_DEPARTURE;
                    readFiles->setFlowTypee(v->idTOBFS, typeofflow);
                }
            }
            enum FlowType typeofflow;
            if(relation->flowTypee!=NOT_DEFINED) {
                if (relation->DestinyStation == v) {
                    typeofflow = FROM_DEPARTURE_TO_ARRIVAL;
                    path.push_back(typeofflow);
                } else {
                    typeofflow = FROM_ARRIVAL_TO_DEPARTURE;
                    path.push_back(typeofflow);
                }
            }
            if(relation->flowTypee==typeofflow){
                path_flow = std::min(path_flow,(relation->Capacity-relation->ActualFlow));
                }
            else{
                path_flow = std::min(path_flow,(relation->ActualFlow));
                }
            }
        int N = 0;
        for(v=dst;v!=src;v=v->parent){
            std::shared_ptr<Trip> relation = trips[v->idTOBFS];
            if(relation->flowTypee==path[N]){
                readFiles->setActualFlow(v->idTOBFS,relation->ActualFlow+path_flow);
            }
            else{
                readFiles->setActualFlow(v->idTOBFS,relation->ActualFlow-path_flow);
            }
            N++;
        }
        max_flow += path_flow;
    }
    return max_flow;
}
//2.2 que por algum motivo nao funciona ainda AHHHHHHHAAAAAAAAAHHHHHHHHHHHH ODEIO PROGRAMAR
std::vector<std::pair<std::shared_ptr<StationNode>,std::shared_ptr<StationNode>>> T2::PairMostCapacity(){
    ReadFiles * readFiles = ReadFiles::getInstance();
    std::vector<std::pair<std::shared_ptr<StationNode>,std::shared_ptr<StationNode>>> pairs;
    std::vector<std::shared_ptr<StationNode>> stationsz = readFiles->getStations();
    std::vector<std::shared_ptr<StationNode>> Stations2iteration = stationsz;
    readFiles->resetVisitedStations();
    readFiles->resetActualFlow();
    int maxflow = INT_MIN;
    for (auto i = stationsz.begin(); i != stationsz.end(); ++i) {
        for (auto j = i; ++j != stationsz.end(); /**/) {
            if (i != j) {
                int kapa = MaxFlowNormal((*i)->station.getName(), (*j)->station.getName());
                if (kapa == maxflow) {

                    std::pair<std::shared_ptr<StationNode>, std::shared_ptr<StationNode>> a = std::make_pair((*i),
                                                                                                             (*j));
                    pairs.push_back(a);

                } else if (kapa > maxflow) {
                    std::pair<std::shared_ptr<StationNode>, std::shared_ptr<StationNode>> a = std::make_pair((*i),
                                                                                                             (*j));
                    pairs.push_back(a);
                    maxflow = kapa;
                    pairs.clear();
                }

            }
        }
    }
    return pairs;
}
//2.3
    map<string, int> T2::MaxFlowEdgeM(std::string Municipality){
        ReadFiles * readFiles = ReadFiles::getInstance();
        std::vector<std::shared_ptr<StationNode>> stationsz = readFiles->getStations();
        std::vector <string> municipality;
        for (auto i = stationsz.begin(); i != stationsz.end(); ++i) {
        if(municipality.empty())
            municipality.push_back((*i)->station.getMunicipality());
        else{
            if(!checkExists(municipality, (*i)->station.getMunicipality()))
                municipality.push_back((*i)->station.getMunicipality());
        }
    }

    double sum = 0;
    std::map<std::string, int> mapa;
    std::vector<std::shared_ptr<Trip>> trips = readFiles->gettrips();
    for(auto& m: municipality){
        for(auto i = stationsz.begin(); i != stationsz.end(); ++i) {
            if(m == (*i)->station.getMunicipality()) {
                for(auto j = trips.begin(); j != trips.end(); ++j) {
                    if((*i) == (*j)->DestinyStation || (*i) == (*j)->StationPartida){
                        sum += (*j)->Capacity;
                    }
                }
            }
        }
        mapa.insert(std::make_pair(m, sum));
    }
    return mapa;
}

map<string,int> T2::MaxFlowEdgeD(std::string Districts){ //disctricts
        ReadFiles * readFiles = ReadFiles::getInstance();
        std::vector<std::shared_ptr<StationNode>> stationsz = readFiles->getStations();
        std::vector <string> districts;
        for (auto i = stationsz.begin(); i != stationsz.end(); ++i) {
        if(districts.empty())
            districts.push_back((*i)->station.getDistrict());
        else{
            if(!checkExists(districts, (*i)->station.getDistrict()))
                districts.push_back((*i)->station.getDistrict());
        }
    }

    double sum = 0;
    std::map<std::string, int> mapa;
    std::vector<std::shared_ptr<Trip>> trips = readFiles->gettrips();
    for(auto& m: districts){
        for(auto i = stationsz.begin(); i != stationsz.end(); ++i) {
            if(m == (*i)->station.getDistrict()) {
                for(auto j = trips.begin(); j != trips.end(); ++j) {
                    if((*i) == (*j)->DestinyStation || (*i) == (*j)->StationPartida){
                        sum += (*j)->Capacity;
                    }
                }
            }
        }
        mapa.insert(std::make_pair(m, sum));
    }
    return mapa;
}

    bool checkExists(std::vector<string> m, std::string n){
        for(auto k:m){
            if(k == n) return true;
        }
        return false;
    }

//2.4
int T2::arriveStation(std::string Destino){
    ReadFiles * readFiles = ReadFiles::getInstance();
    std::shared_ptr<StationNode> dst = readFiles->getStationNode(Destino);
    if(dst.get()==nullptr) return -1;
    readFiles->resetVisitedStations();
    readFiles->resetActualFlow();
    Station supersource = Station("SuperSource");
    StationNode SuperSourceNode = StationNode(supersource);
    readFiles->addStation(SuperSourceNode);
    std::vector<std::shared_ptr<StationNode>> stations = readFiles->getStations();
    int F = readFiles->gettrips().size()-1;
    for(auto it = stations.begin();it!=stations.end();it++){
        auto a = (*it);
        if(a->tripsid.size()==1 && a->station.getName()!=Destino){
            readFiles->addTrip(F++,"SuperSource",a->station.getName(),STANDARD,INT_MAX,0);
        }
    }
    int max_flow = 0;
    std::vector<std::shared_ptr<Trip>> trips = readFiles->gettrips();
    std::shared_ptr<StationNode> v;
    std::shared_ptr<StationNode> u;
    std::vector<enum FlowType> path;
    std::shared_ptr<StationNode> supersourcesharedpt = readFiles->getStationNode("SuperSource");
    if(supersourcesharedpt.get()==nullptr) return -1;
    while(bfs(supersourcesharedpt,dst,readFiles)){
        std::vector<std::shared_ptr<Trip>> trips = readFiles->gettrips();
        int path_flow = INT_MAX;
        for(v=dst;v!=supersourcesharedpt;v=v->parent){
            std::shared_ptr<Trip> relation = trips[v->idTOBFS];
            if(relation->flowTypee==NOT_DEFINED) {
                enum FlowType typeofflow;
                if (relation->DestinyStation == v) {
                    typeofflow = FROM_DEPARTURE_TO_ARRIVAL;
                    readFiles->setFlowTypee(v->idTOBFS, typeofflow);
                } else {
                    typeofflow = FROM_ARRIVAL_TO_DEPARTURE;
                    readFiles->setFlowTypee(v->idTOBFS, typeofflow);
                }
            }
            if(relation->flowTypee!=NOT_DEFINED) {
                enum FlowType typeofflow;
                if (relation->DestinyStation == v) {
                    typeofflow = FROM_DEPARTURE_TO_ARRIVAL;
                    path.push_back(typeofflow);
                } else {
                    typeofflow = FROM_ARRIVAL_TO_DEPARTURE;
                    path.push_back(typeofflow);
                }
            }
            path_flow = std::min(path_flow,(relation->Capacity-relation->ActualFlow));
        }
        int N = path.size();
        for(v=dst;v!=supersourcesharedpt;v=v->parent){
            std::shared_ptr<Trip> relation = trips[v->idTOBFS];
            if(relation->flowTypee==path[N-1]){
                readFiles->setActualFlow(v->idTOBFS,relation->ActualFlow+path_flow);
            }
            else{
                readFiles->setActualFlow(v->idTOBFS,relation->ActualFlow+path_flow);
            }
        }
        N--;
        max_flow += path_flow;
    }
    return max_flow;
}
