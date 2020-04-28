#include "date.h"


Date ParseDate(istream& is)
{
    int year, month, day;
    char c;
    is >> year >> c >> month >> c >> day;
    return Date(year, month, day);
}

ostream& operator<<(ostream& stream, const Date& date)
{
    stream << date.Year() << '-' << date.Month() << '-' << date.Day();
    return stream;
}

