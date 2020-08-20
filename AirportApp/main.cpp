//
//  main.cpp
//  AirportApp
//
//  Created by Артём Калинин on 20.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "Flight.h"
#include "FlightList.h"
#include "Windows.h"
#include <fstream>

void showFlight(Flight& ob, int flag)
{
    cout << string(1000, '\n');
    cout << "Время вылета: " << ob.getDepartureTime() << endl;
    cout << "Продолжительность полета: " << ob.getFlightDuration()[0] << ob.getFlightDuration()[1] << "ч. " <<
        ob.getFlightDuration()[3] << ob.getFlightDuration()[4] << "мин." << endl;
    cout << "Время прибытия: " << ob.getArrivalTime() << endl;
    cout << "Город: " << ob.getDestinationCity() << endl;
    cout << "Номер рейса: " << ob.getFlightNum() << endl;
    cout << "Статус рейса: " << ob.getStatus() << endl;
    cout << "Авиакомпания: " << ob.getAirCompany() << endl;
    cout << "Модель самолёта: " << ob.getPlaneNum() << endl;
    if (flag == 1)
    {
        cout << "Стойки регистрации: " << ob.getReceptionDesks() << endl;
        cout << "Терминал: " << ob.getTerminal() << endl;
        cout << "Выходы на посадку: " << ob.getGate() << endl;

    }
}

int listActions(FlightList& List, int flag)
{
    string ans;
    List.showList(flag);

    if (List.getSize() == 0)
    {
        cout << endl << "Нажмите любую клавишу, чтобы вернуться к выбору онлайн-табло: ";
        cin >> ans;
        cin.ignore(32256, '\n');
        return 0;
    }
    cout << endl << "Введите: Номер записи, чтобы просмотреть о ней более подробную информацию;\n" <<
        "         Город, чтобы осуществить поиск рейсов по городу;\n         0, чтобы вернуться к выбору онлайн-табло: ";
    getline(cin, ans);

    if (ans == "0") return 0;
    else if (ans >= "1" && ans <= to_string(List.getSize()))
    {
        string choice;
        Flight* temp = new Flight();
        temp = List.getHead();
        for (int i = 1; i < stoi(ans); i++)
        {
            temp = temp->pNext;
        }
        showFlight(*temp, flag);
        temp = nullptr;
        delete temp;
        return 1;
    }
    else
    {
        int answer;
        string choice;
        FlightList* OutputList = new FlightList();
        Flight* temp = new Flight();
        temp = List.getHead();
        while (temp)
        {
            if (temp->getDestinationCity() == ans) OutputList->addFlight(*temp);
            temp = temp->pNext;
        }

        if (OutputList->getSize() == 0)
        {
            cout << string(1000, '\n');
            cout << "Некорректный формат ввода. Повторите ввод: " << endl;
        }
        else
        {
            cout << string(1000, '\n');
            while (true)
            {
                OutputList->showList(flag);
                cout << endl << "Введите: Номер записи, чтобы просмотреть о ней более подробную информацию;\n" <<
                    "         0, чтобы вернуться к онлайн-табло: ";
                cin >> answer;
                if (cin.fail() || answer < 0 || answer > OutputList->getSize() || cin.peek() != '\n')
                {
                    cout << string(1000, '\n');
                    cout << "Некорректный формат ввода. Повторите ввод.";
                    cin.clear();
                    cin.ignore(32256, '\n');
                    continue;
                }
                cin.ignore(32256, '\n');

                if (answer != 0)
                {
                    temp = OutputList->getHead();
                    for (int i = 1; i < answer; i++)
                    {
                        temp = temp->pNext;
                    }
                    cout << string(1000, '\n');
                    showFlight(*temp, flag);
                    continue;
                }
                else cout << string(1000, '\n');
                break;
            }
        }
        temp = nullptr;
        OutputList = nullptr;
        delete temp;
        delete OutputList;
        return 1;
    }
}

ostream& operator<<(ostream& os, FlightList& ob)
{
    Flight* temp = new Flight();
    temp = ob.getHead();
    while (temp)
    {
        os << temp->getDepartureTime() << '|' << temp->getFlightDuration() << '|' << temp->getArrivalTime() << '|' <<
           temp->getDestinationCity() << '|' << temp->getFlightNum() << '|' << temp->getStatus() << '|'  <<
            temp->getAirCompany() << '|' << temp->getPlaneNum() << '|' << temp->getTerminal() << '|'  <<
             temp->getReceptionDesks() << '|' << temp->getGate() << "|\n";
        temp = temp->pNext;
    }
    temp = nullptr;
    delete temp;
    return os;
}

istream& operator>>(istream& is, FlightList& ob)
{

    string dump;
    Flight* temp = new Flight();
    while (is.peek() != EOF)
    {
        getline(is, dump, '|');
        temp->setDepartureTime(dump);

        getline(is, dump, '|');
        temp->setFlightDuration(dump);

        getline(is, dump, '|');
        temp->setArrivalTime(dump);

        getline(is, dump, '|');
        temp->setDestinationCity(dump);

        getline(is, dump, '|');
        temp->setFlightNum(dump);

        getline(is, dump, '|');
        temp->setStatus(dump);

        getline(is, dump, '|');
        temp->setAirCompany(dump);

        getline(is, dump, '|');
        temp->setPlaneNum(dump);

        getline(is, dump, '|');
        temp->setTerminal(dump);

        getline(is, dump, '|');
        temp->setReceptionDesks(dump);

        getline(is, dump, '|');
        temp->setGate(stoi(dump));

        is.ignore();

        ob.addFlight(*temp);
    }
    temp = nullptr;
    delete temp;
    return is;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU");
    
    int ans, answer, mainans;
    string choice;
    FlightList* ArrivalList = new FlightList();
    FlightList* DepartureList = new FlightList();

    ifstream fin;
    fin.exceptions(ifstream::badbit | ifstream::failbit);
    try
    {
        fin.open("DepartureList.txt");
        if (fin.peek() != EOF)
        {
            fin >> *DepartureList;
        }
    }
    catch (const exception & ex)
    {
        cout << "Ошибка при открытии файла cо списком рейсов вылета!" << endl;
        cout << ex.what() << endl;
        return 1;
    }
    fin.close();

    try
    {
        fin.open("ArrivalList.txt");
        if (fin.peek() != EOF)
        {
            fin >> *ArrivalList;
        }
    }
    catch (const exception & ex)
    {
        cout << "Ошибка при открытии файла со списком рейсов прилёта!" << endl;
        cout << ex.what() << endl;
        return 1;
    }
    fin.close();

    cout << string(1000, '\n');
    cout << "Добро пожаловать в приложение аэропорта Домодедово г.Москва!" << endl;

    while (true)
    {
        cout << string(50, '-') << endl <<
            "1 - Информация о рейсах" << endl <<
            "2 - Транспорт" << endl <<
            "3 - Услуги" << endl <<
            "4 - Контакты" << endl <<
            "5 - Информация о программе" << endl <<
            "6 - Панель мастера обновления ПО" << endl <<
            "0 - Выход" << endl <<
            string(50, '-') << endl <<
            "Введите номер пункта меню: ";

        cin >> mainans;
        if (cin.fail() || mainans < 0 || mainans > 6 || cin.peek() != '\n')
        {
            cout << string(1000, '\n');
            cout << "Некорректный формат ввода. Повторите ввод:";
            cin.clear();
            cin.ignore(32256, '\n');
            continue;
        }
        cin.ignore(32256, '\n');

        cout << string(1000, '\n');
        switch (mainans)
        {
        case 1:
         {
            while (true)
            {
                cout << string(50, '-') << endl <<
                    "1 - Онлайн-табло вылетов" << endl <<
                    "2 - Онлайн-табло прилетов" << endl <<
                    "0 - Возврат в главное меню" << endl <<
                    string(50, '-') << endl <<
                    "Введите номер пункта меню: ";
                cin >> answer;
                if (cin.fail() || answer < 0 || answer > 2 || cin.peek() != '\n')
                {
                    cout << string(1000, '\n');
                    cout << "Некорректный формат ввода. Повторите ввод:\n";
                    cin.clear();
                    cin.ignore(32256, '\n');
                    continue;
                }
                cin.ignore(32256, '\n');

                cout << string(1000, '\n');
                if (answer == 1)
                {
                    while (listActions(*DepartureList, answer));
                    cout << string(1000, '\n');
                    continue;
                }
                else if (answer == 2)
                {
                    while (listActions(*ArrivalList, answer));
                    cout << string(1000, '\n');
                    continue;
                }
                break;
            }
            break;
        }
          case 2:
        {
            while (true)
            {
                cout << string(50, '-') << endl <<
                    "1 - Аэроэкспресс" << endl <<
                    "2 - Каршеринг" << endl <<
                    "3 - Такси" << endl <<
                    "4 - Пригородный поезд" << endl <<
                    "5 - Автобусы" << endl <<
                    "0 - Возврат в главное меню" << endl <<
                    string(50, '-') << endl <<
                    "Введите номер пункта меню: ";
                cin >> answer;
                if (cin.fail() || answer < 0 || answer > 5 || cin.peek() != '\n')
                {
                    cout << string(1000, '\n');
                    cout << "Некорректный формат ввода. Повторите ввод:\n";
                    cin.clear();
                    cin.ignore(32256, '\n');
                    continue;
                }
                cin.ignore(32256, '\n');
                if (!answer) break;

                string dump;
                try
                {
                    fin.open("Transport.txt");
                    
                    for (int i = 0; i < answer; i++)
                    {
                        getline(fin, dump, '|');
                    }
                }
                catch (const exception & ex)
                {
                    cout << string(1000, '\n');
                    cout << "Ошибка при открытии файла транспорта!" << endl;
                    cout << ex.what() << endl;
                    continue;
                }
                fin.close();


                cout << string(1000, '\n');
                cout << dump << endl;
                continue;
            }
            break;
        }
        case 3:
        {
            while (true)
            {
                cout << string(50, '-') << endl <<
                    "1 - Парковка" << endl <<
                    "2 - Рестораны и кафе" << endl <<
                    "3 - Магазины" << endl <<
                    "4 - Сервисы аэропорта" << endl <<
                    "0 - Возврат в главное меню" << endl <<
                    string(50, '-') << endl <<
                    "Введите номер пункта меню: ";
                cin >> answer;
                if (cin.fail() || answer < 0 || answer > 4 || cin.peek() != '\n')
                {
                    cout << string(1000, '\n');
                    cout << "Некорректный формат ввода. Повторите ввод:\n";
                    cin.clear();
                    cin.ignore(32256, '\n');
                    continue;
                }
                cin.ignore(32256, '\n');
                if (!answer) break;

                string dump;
                try
                {
                    fin.open("Service.txt");

                    for (int i = 0; i < answer; i++)
                    {
                        getline(fin, dump, '|');
                    }
                }
                catch (const exception & ex)
                {
                    cout << string(1000, '\n');
                    cout << "Ошибка при открытии файла c услугами!" << endl;
                    cout << ex.what() << endl;
                    continue;
                }
                fin.close();

                cout << string(1000, '\n');
                cout << dump << endl;
                continue;
            }
            break;
        }
        case 4:
        {
            string dump;
            try
            {
                fin.open("Contacts.txt");
                getline(fin, dump, '|');
            }
            catch (const exception & ex)
            {
                cout << "Ошибка при открытии файла c контактами!" << endl;
                cout << ex.what();
                continue;
            }
            fin.close();

            cout << dump << endl;
            continue;
        }
        case 5:
        {
            cout << "Аэропорт Домодедово г.Москвы 2020\nИнформационное приложение для аэропорта\n" <<
                "Версия (выпуск): 1.0\n(c) Калинин Артём, группа 4832\n";
            continue;
        }
        case 6:
        {
            while (true)
            {
                cout << string(50, '-') << endl <<
                    "1 - Работа с онлайн-табло вылетов" << endl <<
                    "2 - Работа с онлайн-табло прилетов" << endl <<
                    "0 - Возврат в главное меню" << endl <<
                    string(50, '-') << endl <<
                    "Введите номер пункта меню: ";
                cin >> ans;
                if (cin.fail() || ans < 0 || ans > 2 || cin.peek() != '\n')
                {
                    cout << string(1000, '\n');
                    cout << "Некорректный формат ввода. Повторите ввод:\n";
                    cin.clear();
                    cin.ignore(32256, '\n');
                    continue;
                }
                cin.ignore(32256, '\n');
                if (!ans) break;

                cout << string(1000, '\n');
                while (true)
                {
                    cout << string(50, '-') << endl <<
                        "1 - Добавить запись" << endl <<
                        "2 - Редактировать запись" << endl <<
                        "3 - Удалить запись" << endl <<
                        "0 - Вернуться к выбору онлайн-табло" << endl <<
                        string(50, '-') << endl <<
                        "Введите номер пункта меню: ";
                    cin >> answer;
                    if (cin.fail() || answer < 0 || answer > 3 || cin.peek() != '\n')
                    {
                        cout << string(1000, '\n');
                        cout << "Некорректный формат ввода. Повторите ввод:\n";
                        cin.clear();
                        cin.ignore(32256, '\n');
                        continue;
                    }
                    cin.ignore(32256, '\n');
                    break;
                }
                if (!answer)
                {
                    cout << string(1000, '\n');
                    continue;
                }

                cout << string(1000, '\n');
                if (answer == 1)
                {
                    Flight* current = new Flight();
                    if (ans == 1)
                    {
                        if (DepartureList->inputFlightNum(*current) == 0) continue;

                    }
                    else if (ArrivalList->inputFlightNum(*current) == 0) continue;

                    if (current->inputFlight(ans) == 0) continue;

                    ans == 1 ? DepartureList->addFlight(*current) : ArrivalList->addFlight(*current);

                    ans == 1 ? DepartureList->sortDepartureList() : ArrivalList->sortArrivalList();

                    cout << string(1000, '\n');
                    cout << "Успешно добавлено!\n";
                    current = nullptr;
                    delete current;
                    continue;
                }
                else if (answer == 2)
                {
                    string s = "0";
                    while (true)
                    {
                        ans == 1 ? DepartureList->showList(ans) : ArrivalList->showList(ans);
                        if (DepartureList->getSize() == 0 && ans == 1 || ArrivalList->getSize() == 0 && ans == 2)
                        {
                            cout << endl << "Нажмите любую клавишу, чтобы вернуться к выбору онлайн-табло: ";
                            cin >> s;
                            cin.ignore(32256, '\n');
                            break;
                        }
                        else cout << endl << "Введите: Номер записи, чтобы отредактировать её\n" <<
                            "         0, чтобы вернуться к выбору онлайн-табло: ";
                        cin >> answer;

                        if (cin.fail() || answer < 0 || (answer > DepartureList->getSize() && ans == 1) ||
                            (answer > ArrivalList->getSize() && ans == 2) || cin.peek() != '\n')
                        {
                            cout << string(1000, '\n');
                            cout << "Некорректный формат ввода. Повторите ввод:\n";
                            cin.clear();
                            cin.ignore(32256, '\n');
                            continue;
                        }
                        cin.ignore(32256, '\n');
                        break;
                    }
                    if (!answer || s != "0")
                    {
                        cout << string(1000, '\n');
                        continue;
                    }

                    Flight* current = new Flight();
                    ans == 1 ? current = DepartureList->getHead() : current = ArrivalList->getHead();
                    for (int i = 1; i < answer; i++)
                    {
                        current = current->pNext;
                    }

                    cout << string(1000, '\n');
                    while (true)
                    {
                        bool flag = 0;
                        cout << string(50, '-') << endl <<
                            "1 - Изменить время вылета" << endl <<
                            "2 - Изменить продолжительность полёта" << endl <<
                            "3 - Изменить город назначения" << endl <<
                            "4 - Изменить статус рейса" << endl <<
                            "5 - Изменить авиакомпанию" << endl <<
                            "6 - Изменить модель самолёта" << endl <<
                            "7 - Изменить номер рейса" << endl;
                        if (ans == 1)
                        {
                            cout << "8 - Изменить терминал" << endl <<
                                "9 - Изменить стойки регистрации" << endl <<
                                "10 - Изменить выход на посадку" << endl;
                        }
                        cout << "0 - Вернуться к выбору онлайн-табло" << endl <<
                            string(50, '-') << endl <<
                            "Введите номер пункта меню: ";
                        cin >> answer;
                        if (cin.fail() || answer < 0 || answer > 10 || cin.peek() != '\n')
                        {
                            cout << string(1000, '\n');
                            cout << "Некорректный формат ввода. Повторите ввод:\n";
                            cin.clear();
                            cin.ignore(32256, '\n');
                            continue;
                        }
                        cin.ignore(32256, '\n');

                        switch (answer)
                        {
                        case 1:
                        {
                            if (current->inputDepartureTime() == 0) flag = 1;
                            break;
                        }
                        case 2:
                        {
                            string arrivalTime = current->inputFlightDuration(current->getDepartureTime());
                            if (arrivalTime == "0") flag = 1;
                            else
                            {
                                current->setArrivalTime(arrivalTime);
                            }
                            break;
                        }
                        case 3:
                        {
                            if (current->inputDestinationCity() == 0) flag = 1;
                            break;
                        }
                        case 4:
                        {
                            if (current->inputStatus() == 0) flag = 1;
                            break;
                        }
                        case 5:
                        {
                            if (current->inputAirCompany() == 0) flag = 1;
                            break;
                        }
                        case 6:
                        {
                            if (current->inputPlaneNum() == 0) flag = 1;
                            break;
                        }
                        case 7:
                        {
                            if (ans == 1)
                            {
                                if (DepartureList->inputFlightNum(*current) == 0) flag = 1;
                            }
                            else if (ArrivalList->inputFlightNum(*current) == 0) flag = 1;
                            break;
                        }
                        case 8:
                        {
                            if (current->inputTerminal() == 0) flag = 1;
                            break;
                        }
                        case 9:
                        {
                            if (current->inputReceptionDesks() == 0) flag = 1;
                            break;
                        }
                        case 10:
                        {
                            if (current->inputGate() == 0) flag = 1;
                            break;
                        }
                        }

                        if (!flag)
                        {
                            ans == 1 ? DepartureList->sortDepartureList() : ArrivalList->sortArrivalList();
                        }

                        if (!answer || (!flag && answer))
                        {
                            cout << string(1000, '\n');
                            if (!flag && answer) cout << "Успешно изменено!\n";
                        }

                        break;
                    }

                    current = nullptr;
                    delete current;
                    continue;
                }
                else
                {
                    string s = "0";
                    while (true)
                    {
                        ans == 1 ? DepartureList->showList(ans) : ArrivalList->showList(ans);
                        if (DepartureList->getSize() == 0 && ans == 1 || ArrivalList->getSize() == 0 && ans == 2)
                        {
                            cout << endl << "Нажмите любую клавишу, чтобы вернуться к выбору онлайн-табло: ";
                            cin >> s;
                            cin.ignore(32256, '\n');
                            break;
                        }
                        else cout << endl << "Введите: Номер записи, чтобы удалить её\n" <<
                            "         0, чтобы вернуться к выбору онлайн-табло: ";
                        cin >> answer;

                        if (cin.fail() || answer < 0 || (answer > DepartureList->getSize() && ans == 1) ||
                            (answer > ArrivalList->getSize() && ans == 2) || cin.peek() != '\n')
                        {
                            cout << string(1000, '\n');
                            cout << "Некорректный формат ввода. Повторите ввод:\n";
                            cin.clear();
                            cin.ignore(32256, '\n');
                            continue;
                        }
                        cin.ignore(32256, '\n');
                        break;
                    }
                    if (!answer || s != "0")
                    {
                        cout << string(1000, '\n');
                        continue;
                    }

                    Flight* current = new Flight();
                    ans == 1 ? current = DepartureList->getHead() : current = ArrivalList->getHead();
                    for (int i = 1; i < answer; i++)
                    {
                        current = current->pNext;
                    }

                    ans == 1 ? DepartureList->deleteFlight(*current) : ArrivalList->deleteFlight(*current);
                    ans == 1 ? DepartureList->sortDepartureList() : ArrivalList->sortArrivalList();

                    cout << string(1000, '\n');
                    cout << "Успешно удалено!\n";
                    current = nullptr;
                    delete current;
                    continue;
                }
                break;
            }
            break;
        }
        }
        if (!mainans) break;
        else cout << string(1000, '\n');
    }

    ofstream fout;
    fout.exceptions(ofstream::badbit | ofstream::failbit);

    try
    {
        fout.open("DepartureList.txt");
        if (DepartureList->getSize() != 0)
        {
            fout << *DepartureList;
        }
    }
    catch (const exception & ex)
    {
        cout << "Ошибка при открытии файла cо списком рейсов вылета!" << endl;
        cout << ex.what() << endl;
        return 1;
    }
    fout.close();
    
    try
    {
        fout.open("ArrivalList.txt");
        if (ArrivalList->getSize() != 0)
        {
            fout << *ArrivalList;
        }
    }
    catch (const exception & ex)
    {
        cout << "Ошибка при открытии файла cо списком рейсов прилёта!" << endl;
        cout << ex.what() << endl;
        return 1;
    }
    fout.close();

    DepartureList = nullptr;
    ArrivalList = nullptr;
    delete DepartureList;
    delete ArrivalList;

    return 0;
}


