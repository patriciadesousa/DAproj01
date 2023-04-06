#include <iostream>
#include "ReadFiles.h"
#include "T2.h"
#include "Station.h"
//
// Created by Joca on 02/04/2023.
//
int main(){
    ReadFiles * readFiles = ReadFiles::getInstance();
    readFiles->loadFiles();
    /*std::shared_ptr<StationNode> src = readFiles->getStationNode("Oleiros");
    for(auto it=src->tripsid.begin();it!=src->tripsid.end();it++){
        std::cout<<*it<<"\n";
    }*/
    std::cout<<T2::MaxFlowNormal("Entroncamento","Santarém");
    return 0;
}