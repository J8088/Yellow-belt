#include <iostream>
#include "phone_number.h"

using namespace std;

int main() {
    PhoneNumber pn = PhoneNumber("+--");
    cout << pn.GetCountryCode() << endl;
    cout << pn.GetCityCode() << endl;
    cout << pn.GetLocalNumber() << endl;
    cout << pn.GetInternationalNumber() << endl;
    return 0;
}