#pragma once

#include <iostream>

using namespace std;

class Database
{
public:
    void Add(Data date, string event);

    void Print(ostream& s);
};
