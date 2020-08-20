//
//  FlightList.cpp
//  AirportApp
//
//  Created by Артём Калинин on 20.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "FlightList.h"

FlightList::FlightList()
{
    Size = 0;
    head = nullptr;
}

FlightList::~FlightList()
{
    clear();
}

void FlightList::popFront()
{
    Flight* temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

void FlightList::clear()
{
    while (Size)
    {
        popFront();
    }
}

void FlightList::showList(const int flag)
{
    string dump;

    if (!Size)
    {
        cout << endl << "Список пуст!" << endl;
        return;
    }

    Flight* current = this->head;
    int count = 1;
    dump.append(94, '-');
    dump.push_back('\n');
    flag == 1 ? dump.append("| № | Время вылета | Город") : dump.append("| № | Время прилета | Город");
    dump.append(15, ' ');
    dump.append("| Статус");
    dump.append(16, ' ');
    dump.append("| Рейс №");
    dump.append(9, ' ');
    dump.append("| Терминал ");
    dump.append("|\n");
    while (current)
    {
        dump.append("| ");
        dump.append(to_string(count));
        flag == 1 ? dump.append(" | " + current->getDepartureTime()) : dump.append(" | " + current->getArrivalTime());
        flag == 1 ? dump.append(8, ' ') : dump.append(9, ' ');
        dump.append("| " + current->getDestinationCity());
        dump.append(20 - current->getDestinationCity().length(), ' ');
        dump.append("| " + current->getStatus());
        dump.append(22 - current->getStatus().length(), ' ');
        dump.append("| " + current->getFlightNum());
        dump.append(15 - current->getFlightNum().length(), ' ');
        dump.append("| " + current->getTerminal());
        dump.append(8, ' ');
        dump.append("|\n");
        count++;
        current = current->pNext;
    }
    dump.append(94, '-');
    cout << dump << endl;
    delete current;
}

int FlightList::getSize()
{
    return this->Size;
}

Flight* FlightList::getHead()
{
    return this->head;
}

void FlightList::addFlight(Flight input)
{
    input.pNext = nullptr;
    if (head == nullptr)
    {
        head = new Flight(input);
    }
    else
    {
        Flight* current = head;
        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Flight(input);
    }
    Size++;
}

void FlightList::deleteFlight(Flight& input)
{
    if (input == *head) popFront();
    else
    {
        Flight* previous = head;
        while (*(previous->pNext) != input)
        {
            previous = previous->pNext;
        }
        previous->pNext = input.pNext;
        delete previous;
        Size--;
    }
}

void FlightList::sortDepartureList()
{
    if (Size == 0) return;

    Flight* current = new Flight();
    Flight* previous = new Flight();
    Flight* next = new Flight();
    while (true)
    {
        int flag = 0;
        current = head;
        while (current->pNext != nullptr)
        {
            for (size_t i = 0; i < current->getDepartureTime().length(); i++)
            {
                if (static_cast<int>(current->getDepartureTime()[i]) <
                    static_cast<int>(current->pNext->getDepartureTime()[i]))
                {
                    current = current->pNext;
                    break;
                }
                else if (static_cast<int>(current->getDepartureTime()[i]) >
                    static_cast<int>(current->pNext->getDepartureTime()[i]))
                {
                    if (current != head)
                    {
                        previous = head;
                        while (previous->pNext != current)
                        {
                            previous = previous->pNext;
                        }
                        next = current->pNext;
                        current->pNext = next->pNext;
                        next->pNext = current;
                        previous->pNext = next;
                    }
                    else
                    {
                        next = head->pNext;
                        head->pNext = next->pNext;
                        next->pNext = head;
                        head = next;
                        current = next->pNext;
                    }
                    flag++;
                    break;
                }
                else continue;
            }
        }
        if (flag == 0) break;
    }
    previous = nullptr;
    current = nullptr;
    next = nullptr;
    delete previous;
    delete current;
    delete next;
}

void FlightList::sortArrivalList()
{
    if (Size == 0) return;

    Flight* current = new Flight();
    Flight* previous = new Flight();
    Flight* next = new Flight();
    while (true)
    {
        int flag = 0;
        current = head;
        while (current->pNext != nullptr)
        {
            for (size_t i = 0; i < current->getArrivalTime().length(); i++)
            {
                if (static_cast<int>(current->getArrivalTime()[i]) <
                    static_cast<int>(current->pNext->getArrivalTime()[i]))
                {
                    current = current->pNext;
                    break;
                }
                else if (static_cast<int>(current->getArrivalTime()[i]) >
                    static_cast<int>(current->pNext->getArrivalTime()[i]))
                {
                    if (current != head)
                    {
                        previous = head;
                        while (previous->pNext != current)
                        {
                            previous = previous->pNext;
                        }
                        next = current->pNext;
                        current->pNext = next->pNext;
                        next->pNext = current;
                        previous->pNext = next;
                    }
                    else
                    {
                        next = head->pNext;
                        head->pNext = next->pNext;
                        next->pNext = head;
                        head = next;
                        current = next->pNext;
                    }
                    flag++;
                    break;
                }
                else continue;
            }
        }
        if (flag == 0) break;
    }
    previous = nullptr;
    current = nullptr;
    next = nullptr;
    delete previous;
    delete current;
    delete next;
}

bool FlightList::inputFlightNum(Flight& input)
{
    string flightNum;
    cout << "Введите номер рейса: ";
    getline(cin, flightNum);
    if (input.isCorrectFlight(flightNum) == 0)
    {
        cout << string(1000, '\n');
        cout << "Номер рейса должен иметь формат: две прописные латинские буквы, затем через пробел четыре цифры!" << endl;
        return false;
    }
    Flight* current = head;
    while (current)
    {
        if (current->getFlightNum() == flightNum)
        {
            cout << string(1000, '\n');
            cout << "Рейс с таким номером уже есть в списке!" << endl;
            return false;
        }
        current = current->pNext;
    }
    input.setFlightNum(flightNum);
    current = nullptr;
    delete current;
    return true;
}
