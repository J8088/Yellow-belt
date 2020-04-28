#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

class Figure
{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure
{
public:
    Triangle(int a, int b, int c) : A(a), B(b), C(c) {}
    string Name() const override { return "TRIANGLE"; };
    double Perimeter() const override { return (A + B + C); };
    double Area() const override
    {
        double p = Perimeter() / 2.;
        return sqrt(p * (p - A) * (p - B) * (p - C));
    };

private:
    int A;
    int B;
    int C;
};

class Rect : public Figure
{
public:
    Rect(int a, int b) : A(a), B(b) {}
    string Name() const override { return "RECT"; };
    double Perimeter() const override { return (A + B) * 2; };
    double Area() const override { return A * B; };

private:
    int A;
    int B;
};

class Circle : public Figure
{
public:
    Circle(int r) : R(r) {}
    string Name() const override { return "CIRCLE"; };
    double Perimeter() const override { return 2 * 3.14 * R; };
    double Area() const override { return 3.14 * R * R; }

private:
    int R;
};

shared_ptr<Figure> CreateFigure(istringstream& is)
{
    shared_ptr<Figure> res;
    string type;
    is >> type;
    if (type == "CIRCLE")
    {
        int r;
        is >> r;
        res = make_shared<Circle>(r);
    }
    else if (type == "RECT")
    {
        int a, b;
        is >> a >> b;
        res = make_shared<Rect>(a, b);
    }
    else if (type == "TRIANGLE")
    {
        int a, b, c;
        is >> a >> b >> c;
        res = make_shared<Triangle>(a, b, c);
    }
    return res;
};

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}