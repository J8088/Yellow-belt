#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


class Person
{
public:
    Person(const string& profession, const string& name) : profession_(profession), name_(name) {}
    virtual void Walk(const string& destination) const
    {
        cout << Profession_Name() << " walks to: " << destination << endl;
    };

    string Profession_Name() const {
        stringstream s;
        s << Profession() << ": " << Name();
        return s.str();
    }

    string Profession() const { return profession_; }
    string Name() const { return name_; }

protected:
    const string name_;
    const string profession_;
};

class Student : public Person {
public:
    Student(const string& name, const string& favourite_song) : Person("Student", name), favourite_song_(favourite_song) {}
    void Learn() {
        cout << Profession_Name() << " learns" << endl;
    }

    void SingSong() const {
        cout << Profession_Name() << " sings a song: " << favourite_song_ << endl;
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

private:
    const string favourite_song_;
};

class Teacher : public Person {
public:

    Teacher(const string& name,const string& subject) : Person("Teacher", name), subject_(subject) {}

    void Teach() {
        cout << Profession_Name() << " teaches: " << subject_ << endl;
    }

private:
    string subject_;
};

class Policeman : public Person {
public:
    Policeman(const string& name) : Person("Policeman", name) {}

    void Check(Person& person) {
        cout << Profession_Name() << " checks "<< person.Profession()<< ". "
        << person.Profession() << "'s name is: " << person.Name() << endl;
    }
};

void VisitPlaces(Person& person,const vector<string>& places) {
    for (auto place : places)
        person.Walk(place);
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}

