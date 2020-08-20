//
//  FlightList.h
//  AirportApp
//
//  Created by Артём Калинин on 20.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef FlightList_h
#define FlightList_h

#include <iostream>
#include <string>
#include "Flight.h"

using namespace std;

class FlightList
{
    int Size;
    Flight* head;

public:
    FlightList();
    ~FlightList();
    void clear();
    void sortDepartureList();
    void sortArrivalList();
    void popFront();
    void showList(const int flag);
    int getSize();
    Flight* getHead();
    void addFlight(Flight input);
    void deleteFlight(Flight& input);
    bool inputFlightNum(Flight& input);
};

#endif /* FlightList_h */
