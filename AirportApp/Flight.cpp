//
//  Flight.cpp
//  AirportApp
//
//  Created by Артём Калинин on 20.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "Flight.h"
#include "FlightList.h"

Flight::Flight()
{
    departureTime = "";
    arrivalTime = "";
    flightDuration = "";
    destinationCity = "";
    status = "";
    airCompany = "";
    planeNum = "";
    flightNum = "";
    receptionDesks = "";
    terminal = "";
    gate = 0;
    pNext = nullptr;
}

string Flight::getDepartureTime()
{
    return this->departureTime;
}

string Flight::getArrivalTime()
{
    return this->arrivalTime;
}

string Flight::getFlightDuration()
{
    return this->flightDuration;
}

string Flight::getDestinationCity()
{
    return this->destinationCity;
}

string Flight::getStatus()
{
    return this->status;
}

string Flight::getAirCompany()
{
    return this->airCompany;
}

string Flight::getPlaneNum()
{
    return this->planeNum;
}

string Flight::getFlightNum()
{
    return this->flightNum;
}

string Flight::getTerminal()
{
    return this->terminal;
}

string Flight::getReceptionDesks()
{
    return this->receptionDesks;
}

int Flight::getGate()
{
    return this->gate;
}

void Flight::setDepartureTime(const string time)
{
    this->departureTime = time;
}

void Flight::setArrivalTime(const string time)
{
    this->arrivalTime = time;
}

void Flight::setFlightDuration(const string time)
{
    this->flightDuration = time;
}

void Flight::setDestinationCity(const string destinationCity)
{
    this->destinationCity = destinationCity;
}

void Flight::setStatus(const string status)
{
    this->status = status;
}

void Flight::setAirCompany(const string airCompany)
{
    this->airCompany = airCompany;
}

void Flight::setPlaneNum(const string planeNum)
{
    this->planeNum = planeNum;
}

void Flight::setFlightNum(const string flightNum)
{
    this->flightNum = flightNum;
}

void Flight::setTerminal(const string terminal)
{
    this->terminal = terminal;
}

void Flight::setReceptionDesks(const string receptionDesks)
{
    this->receptionDesks = receptionDesks;
}

void Flight::setGate(const int gate)
{
    this->gate = gate;
}

bool Flight::isCorrectTime(const string time)
{
    if (time == "") return false;
    size_t pos = time.find(':');
    if (pos == 2)
    {
        if (time[0] == '0' || time[0] == '1')
        {
            if (time[1] >= '0' && time[1] <= '9') return true;
        }

        else if (time[0] == '2')
        {
            if (time[1] >= '0' && time[1] <= '3') return true;
        }

        else if (time[3] >= '0' && time[3] <= '5')
        {
            if (time[4] >= '0' && time[4] <= '9') return true;
        }
    }
    return false;
}

bool Flight::isCorrectCity(const string destinationCity)
{
    if (destinationCity == "") return false;
    for (const auto& c : destinationCity)
    {
        if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я') || c == '-' || c == ' ')
            continue;
        else return false;
    }
    return true;
}

bool Flight::isCorrectStatus(const string status)
{
    if (status == "") return false;
    for (const auto& c : status)
    {
        if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я') || c == ' ')
            continue;
        else return false;
    }
    return true;
}

bool Flight::isCorrectCompany(const string airCompany)
{
    if (airCompany == "") return false;
    for (const auto& c : airCompany)
    {
        if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я')
            || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ' || (c >= '0' && c <= '9'))
            continue;
        else return false;
    }
    return true;
}

bool Flight::isCorrectPlane(const string planeNum)
{
    if (planeNum == "") return false;
    for (const auto& c : planeNum)
    {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '-' || c == ' ' || (c >= '0' && c <= '9'))
            continue;
        else return false;
    }
    return true;
}

bool Flight::isCorrectFlight(string flightNum)
{
    if (flightNum == "") return false;
    size_t pos = flightNum.find(' ');
    if (pos == 2)
    {
        if (flightNum[0] < 'A' || flightNum[0] > 'Z') return false;
        if (flightNum[1] < 'A' || flightNum[1] > 'Z') return false;

        flightNum = flightNum.substr(pos + 1);
        if (flightNum.size() != 4) return false;
        for (const auto& c : flightNum)
        {
            if (c < '0' || c > '9') return false;
        }
    }
    else return false;

    return true;
}

bool Flight::isCorrectTerminal(const string terminal)
{
    if (terminal == "") return false;
    for (const auto& c : terminal)
    {
        if (terminal.size() == 1 && c >= 'A' && c <= 'Z') return true;
    }
    return false;
}

bool Flight::isCorrectReception(const string receptionDesks)
{
    if (receptionDesks == "") return false;
    for (const auto& c : receptionDesks)
    {
        if ((c >= '0' && c <= '9') || c == ',' || c == ' ')
            continue;
        else return false;
    }
    return true;
}

bool Flight::isCorrectGate(const int gate)
{
    if (gate < 1 || gate > 199) return false;
    return true;
}

bool Flight::inputFlight(const int flag)
{
    if (inputDepartureTime() == 0) return false;

    string arrivalTime = inputFlightDuration(departureTime);
    if (arrivalTime == "0") return false;

    setArrivalTime(arrivalTime);

    if (inputDestinationCity() == 0) return false;

    if (inputStatus() == 0) return false;

    if (inputAirCompany() == 0) return false;

    if (inputPlaneNum() == 0) return false;

    if (inputTerminal() == 0) return false;

    if (flag == 1)
    {
        if (inputReceptionDesks() == 0) return false;

        if (inputGate() == 0) return false;
    }

    return true;
}

bool Flight::inputDepartureTime()
{
    string str;
    cout << "Введите время вылета: ";
    getline(cin, str);
    if (isCorrectTime(str))
    {
        setDepartureTime(str);
        return true;
    }
    else
    {
        cout << string(1000, '\n');
        cout << "Время должно иметь формат ЦЦ:ЦЦ!" << endl;
        return false;
    }
}

string Flight::inputFlightDuration(const string departureTime)
{
    string str, arrivalTime;
    cout << "Введите продолжительность полёта: ";
    getline(cin, str);
    if (!isCorrectTime(str))
    {
        cout << string(1000, '\n');
        cout << "Время должно иметь формат ЦЦ:ЦЦ!" << endl;
        return "0";
    }

    setFlightDuration(str);

    int hour = stoi(departureTime.substr(0, 2));
    int minute = stoi(departureTime.substr(3, 2));

    int hourInput = stoi(str.substr(0, 2));
    int minuteInput = stoi(str.substr(3, 2));

    int hourResult = hour + hourInput;
    int minuteResult = minute + minuteInput;

    if (minuteResult > 59)
    {
        minuteResult = minuteResult - 60;
        hourResult += 1;
    }
    if (hourResult > 23) hourResult = hourResult - 24;

    if (hourResult <= 9) arrivalTime.push_back('0');
    arrivalTime.append(to_string(hourResult));
    arrivalTime.push_back(':');
    if (minuteResult <= 9) arrivalTime.push_back('0');
    arrivalTime.append(to_string(minuteResult));

    return arrivalTime;
}

bool Flight::inputDestinationCity()
{
    string str;
    cout << "Введите город назначения: ";
    getline(cin, str);
    if (isCorrectCity(str))
    {
        setDestinationCity(str);
        return true;
    }
    else
    {
        cout << string(1000, '\n');
        cout << "Город назначения должен состоять только из букв кириллицы/символов тире или пробела!" << endl;
        return false;
    }
}

bool Flight::inputStatus()
{
    string str;
    cout << "Введите статус рейса: ";
    getline(cin, str);
    if (isCorrectStatus(str))
    {
        setStatus(str);
        return true;
    }
    else
    {
        cout << string(1000, '\n');
        cout << "Статус рейса должен состоять только из букв кириллицы/символов пробела!" << endl;
        return false;
    }
}

bool Flight::inputAirCompany()
{
    string str;
    cout << "Введите авиакомпанию: ";
    getline(cin, str);
    if (isCorrectCompany(str))
    {
        setAirCompany(str);
        return true;
    }
    else
    {
        cout << string(1000, '\n');
        cout << "Авиакомпания должна состоять только из букв кириллицы/латиницы/цифр/символов пробела!" << endl;
        return false;
    }
}

bool Flight::inputPlaneNum()
{
    string str;
    cout << "Введите модель самолёта: ";
    getline(cin, str);
    if (isCorrectPlane(str))
    {
        setPlaneNum(str);
        return true;
    }
    else
    {
        cout << string(1000, '\n');
        cout << "Модель самолета должна состоять только из букв латиницы/цифр/символов тире или пробела!" << endl;
        return false;
    }
    
}

bool Flight::inputTerminal()
{
    string str;
    cout << "Введите терминал: ";
    getline(cin, str);
    if (isCorrectTerminal(str))
    {
        setTerminal(str);
        return true;
    }
    else
    {
        cout << string(1000, '\n');
        cout << "Терминал должен состоять только из прописной латинской буквы!" << endl;
        return false;
    }
}

bool Flight::inputReceptionDesks()
{
    string str;
    cout << "Введите стойки регистрации: ";
    getline(cin, str);
    if (isCorrectReception(str))
    {
        setReceptionDesks(str);
        return true;
    }
    else
    {
        cout << string(1000, '\n');
        cout << "Стойки регистрации должны состоять только из цифр/символов запятой или пробела!" << endl;
        return false;
    }
}

bool Flight::inputGate()
{
    int i;
    cout << "Введите выход на посадку: ";
    cin >> i;
    if (!cin.fail() && isCorrectGate(i) && cin.peek() == '\n')
    {
        setGate(i);
        cin.ignore(32256, '\n');
        return true;
    }
    else
    {
        cin.clear();
        cin.ignore(32256, '\n');
        cout << string(1000, '\n');
        cout << "Выход на посадку должен состоять только из положительного числа, меньшего 200!" << endl;
        return false;
    }
}

bool Flight::operator== (const Flight& ob)
{
    return this->departureTime == ob.departureTime && this->flightDuration == ob.flightDuration
        && this->arrivalTime == ob.arrivalTime && this->destinationCity == ob.destinationCity &&
        this->flightNum == ob.flightNum && this->status == ob.status && this->airCompany == ob.airCompany &&
        this->planeNum == ob.planeNum && this->receptionDesks == ob.receptionDesks && this->terminal == ob.terminal
        && this->gate == ob.gate;
}

bool Flight::operator!= (const Flight& ob)
{
    return this->departureTime != ob.departureTime || this->flightDuration != ob.flightDuration
        || this->arrivalTime != ob.arrivalTime || this->destinationCity != ob.destinationCity ||
        this->flightNum != ob.flightNum || this->status != ob.status || this->airCompany != ob.airCompany ||
        this->planeNum != ob.planeNum || this->receptionDesks != ob.receptionDesks || this->terminal != ob.terminal
        || this->gate != ob.gate;
}
