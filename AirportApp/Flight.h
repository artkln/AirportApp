//
//  Flight.h
//  AirportApp
//
//  Created by Артём Калинин on 20.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef Flight_h
#define Flight_h

#include <iostream>
#include <string>
using namespace std;

class Flight
{
    string departureTime;
    string flightDuration;
    string arrivalTime;
    string destinationCity;
    string flightNum;
    string status;
    string airCompany;
    string planeNum;
    string receptionDesks;
    string terminal;
    int gate;

public:
    Flight* pNext;

    Flight();

    string getDepartureTime();
    string getArrivalTime();
    string getFlightDuration();
    string getDestinationCity();
    string getStatus();
    string getAirCompany();
    string getPlaneNum();
    string getFlightNum();
    string getTerminal();
    string getReceptionDesks();
    int getGate();

    void setDepartureTime(const string time);
    void setArrivalTime(const string time);
    void setFlightDuration(const string time);
    void setDestinationCity(const string destinationCity);
    void setStatus(const string status);
    void setAirCompany(const string airCompany);
    void setPlaneNum(const string planeNum);
    void setFlightNum(const string flightNum);
    void setTerminal(const string terminal);
    void setReceptionDesks(const string receptionDesks);
    void setGate(const int gate);

    bool isCorrectTime(const string time);
    bool isCorrectCity(const string destinationCity);
    bool isCorrectStatus(const string status);
    bool isCorrectCompany(const string airCompany);
    bool isCorrectPlane(const string planeNum);
    bool isCorrectFlight(const string flightNum);
    bool isCorrectTerminal(const string terminal);
    bool isCorrectReception(const string receptionDesks);
    bool isCorrectGate(const int gate);

    bool inputFlight(const int flag);
    bool inputDepartureTime();
    string inputFlightDuration(const string departureTime);
    bool inputDestinationCity();
    bool inputStatus();
    bool inputAirCompany();
    bool inputPlaneNum();
    bool inputTerminal();
    bool inputReceptionDesks();
    bool inputGate();

    bool operator==(const Flight& ob);
    bool operator!=(const Flight& ob);
};

#endif /* Flight_h */
