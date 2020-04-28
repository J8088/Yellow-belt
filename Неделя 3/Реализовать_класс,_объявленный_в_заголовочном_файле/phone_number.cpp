#include "phone_number.h"

#include <sstream>
#include <iostream>

using namespace std;

    /* Принимает строку в формате +XXX-YYY-ZZZZZZ
       Часть от '+' до первого '-' - это код страны.
       Часть между первым и вторым символами '-' - код города
       Всё, что идёт после второго символа '-' - местный номер.
       Код страны, код города и местный номер не должны быть пустыми.
       Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

       Примеры:
       * +7-495-111-22-33
       * +7-495-1112233
       * +323-22-460002
       * +1-2-coursera-cpp
       * 1-2-333 - некорректный номер - не начинается на '+'
       * +7-1233 - некорректный номер - есть только код страны и города
    */
    PhoneNumber::PhoneNumber(const string &international_number)
    {
            stringstream ss(international_number);
            char c;
            ss >> c;
            if (c != '+')
                throw invalid_argument("");
            do {
                ss >> c;
                if (!ss) throw invalid_argument("");
                if (c == '-') break;
                country_code_ += c;
            } while (1);
            do {
                ss >> c;
                if (!ss) throw invalid_argument("");
                if (c == '-') break;
                city_code_ += c;
            } while (1);
            do {
                ss >> c;
                if (!ss) break;
                local_number_ += c;
            } while (1);
        if ((country_code_ == "") || (city_code_ == "") || (local_number_ == ""))
            throw invalid_argument("");
    }

string PhoneNumber::GetCountryCode() const {
        return country_code_; }

string PhoneNumber::GetCityCode() const {
    return city_code_; }

string PhoneNumber::GetLocalNumber() const {
    return local_number_; }

string PhoneNumber::GetInternationalNumber() const {
    return '+' + country_code_ + '-' + city_code_ + '-' + local_number_; }

