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
    return 0;
}