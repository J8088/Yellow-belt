#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
enum class Gender {
    FEMALE,
    MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};


// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
            begin(range_copy), middle, end(range_copy),
            [](const Person& lhs, const Person& rhs) {
                return lhs.age < rhs.age;
            }
    );
    return middle->age;
}
*/

template <typename Func>

void Mid_with_parametr(vector<Person> persons, string condition, Func foo)
{
    vector<Person> temp;
    copy_if(persons.begin(), persons.end(), back_inserter(temp), foo);
    int mid_age = ComputeMedianAge(temp.begin(), temp.end());
    cout << "Median age " << condition << "= " << mid_age << endl;
}


void PrintStats(vector<Person> persons)
{
    Mid_with_parametr(persons, "", [](Person p){ return true; });
    Mid_with_parametr(persons, "for females ", [](Person p){ return p.gender == Gender::FEMALE; });
    Mid_with_parametr(persons, "for males ", [](Person p){ return p.gender == Gender::MALE; });
    Mid_with_parametr(persons, "for employed females ", [](Person p){ return (p.gender == Gender::FEMALE) && p.is_employed; });
    Mid_with_parametr(persons, "for unemployed females ", [](Person p){ return (p.gender == Gender::FEMALE) && !p.is_employed; });
    Mid_with_parametr(persons, "for employed males ", [](Person p){ return (p.gender == Gender::MALE) && p.is_employed; });
    Mid_with_parametr(persons, "for unemployed males ", [](Person p){ return (p.gender == Gender::MALE) && !p.is_employed; });
}

int main() {
    vector<Person> persons = {
            {31, Gender::MALE, false},
            {40, Gender::FEMALE, true},
            {24, Gender::MALE, true},
            {20, Gender::FEMALE, true},
            {80, Gender::FEMALE, false},
            {78, Gender::MALE, false},
            {10, Gender::FEMALE, false},
            {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}
