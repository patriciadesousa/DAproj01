//
// Created by Joca on 04/04/2023.
//

#ifndef FIRSTDA_T2_H
#define FIRSTDA_T2_H


#include <string>
#include "ReadFiles.h"
#include "Station.h"

struct T2{
    static int MaxFlowNormal(std::string Partida, std::string Chegada);
    static bool bfs(std::shared_ptr<StationNode> src, std::shared_ptr<StationNode> dst);
};


#endif //FIRSTDA_T2_H
