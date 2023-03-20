#include "Menu.h"

void Menu::appMenu() {
    cout << "##########################################" << endl;
    cout << "                                          " << endl;
    cout << "  RAILWAY NETWORK                         " << endl;
    cout << "                                          " << endl;
    cout << "    1-> DATA AND INTERFACE                " << endl;
    cout << "    2-> BASIC SERVICE METRICS             " << endl;
    cout << "    3-> OPERATION COST OPTIMIZATION       " << endl;
    cout << "    4-> RELIABILITY AND SENSITIVITY       " << endl;
    cout << "    0-> EXIT                              " << endl;
    cout << "                                          " << endl;
    cout << "##########################################" << endl;
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: dataInterfaceMenu(); break;
            case 2: basicServiceMetricMenu(); break;
            case 3: operationCostMenu(); break;
            case 4: reliabilityAndSensitivityMenu(); break;
            case 0: exit(0);
            default: cout << "INVALID OPTION\nTry again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3 && option != 4);
}

void Menu::dataInterfaceMenu() {
    cout << "##########################################" << endl;
    cout << "                                          " << endl;
    cout << "  RAILWAY NETWORK                         " << endl;
    cout << "                                          " << endl;
    cout << "    1->                                   " << endl;
    cout << "    2->                                   " << endl;
    cout << "    3->                                   " << endl;
    cout << "    0-> BACK                              " << endl;
    cout << "                                          " << endl;
    cout << "##########################################" << endl;
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: dataInterfaceMenu(); break;
            case 2: basicServiceMetricMenu(); break;
            case 3: operationCostMenu(); break;
            case 4: reliabilityAndSensitivityMenu(); break;
            case 0: appMenu();
            default: cout << "INVALID OPTION\nTry again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3);
}

void Menu::basicServiceMetricMenu() {
    cout << "##########################################" << endl;
    cout << "                                          " << endl;
    cout << "  RAILWAY NETWORK                         " << endl;
    cout << "                                          " << endl;
    cout << "    1->                                   " << endl;
    cout << "    2->                                   " << endl;
    cout << "    3->                                   " << endl;
    cout << "    0-> BACK                              " << endl;
    cout << "                                          " << endl;
    cout << "##########################################" << endl;
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 0: appMenu();
            default: cout << "INVALID OPTION\nTry again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3);
}

void Menu::operationCostMenu() {
    cout << "##########################################" << endl;
    cout << "                                          " << endl;
    cout << "  RAILWAY NETWORK                         " << endl;
    cout << "                                          " << endl;
    cout << "    1->                                   " << endl;
    cout << "    2->                                   " << endl;
    cout << "    3->                                   " << endl;
    cout << "    0-> BACK                              " << endl;
    cout << "                                          " << endl;
    cout << "##########################################" << endl;
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 0: appMenu();
            default: cout << "INVALID OPTION\nTry again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3);
}

void Menu::reliabilityAndSensitivityMenu() {
    cout << "##########################################" << endl;
    cout << "                                          " << endl;
    cout << "  RAILWAY NETWORK                         " << endl;
    cout << "                                          " << endl;
    cout << "    1->                                   " << endl;
    cout << "    2->                                   " << endl;
    cout << "    3->                                   " << endl;
    cout << "    0-> BACK                              " << endl;
    cout << "                                          " << endl;
    cout << "##########################################" << endl;
    int option;
    do{
        cin >> option;
        switch(option) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 0: appMenu();
            default: cout << "INVALID OPTION\nTry again: ";
        }
    } while(option != 0 && option != 1 && option != 2 && option != 3);
}