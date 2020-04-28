#pragma once

#include <iostream>

using namespace std;

class Date
{
    //надо ли в объявлении указывать конструктор??
public:
    Date(const int& year, const int& month, const int& day) : year_(year), month_(month), day_(day) {};

    int Year() const { return year_; }
    int Month() const { return month_; }
    int Day() const { return day_; }
private:
    const int year_;
    const int month_;
    const int day_;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& stream, const Date&);