#include <queue>
#include <iostream>
#include "T2.h"

ReadFiles * readFiles = ReadFiles::getInstance();

bool T2::bfs(std::shared_ptr<StationNode> src, std::shared_ptr<StationNode> dst)
{
    std::queue<std::shared_ptr<StationNode>> q;
    q.push(src);
    readFiles->resetVisitedStations();
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
    std::shared_ptr<StationNode> src = readFiles->getStationNode(Partida);
    if(src.get()== nullptr) return -1;
    std::shared_ptr<StationNode> dst = readFiles->getStationNode(Chegada);
    if(dst.get()== nullptr) return -1;
    readFiles->resetVisitedStations();
    readFiles->resetActualFlow();
    int max_flow = 0;
    std::shared_ptr<StationNode> v;
    std::shared_ptr<StationNode> u;
    std::vector<enum FlowType> path;
    while(bfs(src,dst)){
        std::vector<std::shared_ptr<Trip>> trips = readFiles->gettrips();
        int path_flow = INT_MAX;
        for(v=dst;v!=src;v=v->parent){
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
        for(v=dst;v!=src;v=v->parent){
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