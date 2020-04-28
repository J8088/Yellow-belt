#include<iostream>
#include <map>
#include <set>
#include <vector>
#include <exception>
#include <sstream>
#include<string>
#include<algorithm>


using namespace std;
/*

void Pozitive(int& a)
{
    if (a < 0)
        a = -a;
}

int NOD(int a, int b) {

    while (a != b) {
        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        b = b - a;
    }
    return a;
}

int NOK(const int& a, const int& b)
{
    return a * b / NOD(a, b);
}

void Cut(int& a, int& b)
{
    //положительное (0) или отрицательное (1)
    bool sign = (((a < 0) && (b > 0)) || ((a > 0) && (b < 0)));
    //делаю 2 положительных числа
    Pozitive(a);
    Pozitive(b);
    int d = NOD(a, b);
    a /= d;
    b /= d;
    //возвращаю знак
    if (sign) a *= -1;
}



class Rational {
public:
    Rational()
    {
        num = 0;
        denom = 1;
    }
    Rational(int numerator, int denominator)
    {
        if (denominator == 0)
            throw  invalid_argument("");
        //если 0
        if (numerator == 0)
        {
            denom = 1;
            num = 0;
            return;
        }
        Cut(numerator, denominator);
        num = numerator;
        denom = denominator;
    }
    int Numerator() const
    {
        return num;
    }
    int Denominator() const
    {
        return denom;
    }
private:
    int num;
    int denom;
};


Rational operator+(const Rational& l, const Rational& r) {
    int denom_new = NOK(l.Denominator(), r.Denominator());
    int num_new = (denom_new / l.Denominator()) * l.Numerator() + (denom_new / r.Denominator()) * r.Numerator();
    return  Rational(num_new, denom_new);
}

Rational operator-(const Rational& l, const Rational& r) {
    int denom_new = NOK(l.Denominator(), r.Denominator());
    int num_new = (denom_new / l.Denominator()) * l.Numerator() - (denom_new / r.Denominator()) * r.Numerator();
    return  Rational(num_new, denom_new);
}

bool operator==(const Rational& l, const Rational& r) {
    return ((l.Numerator() == r.Numerator()) && (l.Denominator() == r.Denominator()));
}

Rational operator*(const Rational& l, const Rational& r) {
    return  Rational(l.Numerator() * r.Numerator(), l.Denominator() * r.Denominator());
}

Rational operator/(const Rational& l, const Rational& r) {
    if (r.Numerator() == 0)
        throw domain_error("");
    Rational temp(r.Denominator(), r.Numerator());
    return  l * temp;
}

ostream& operator<<(ostream& stream, const Rational& rational){
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& rational) {
    if(stream.good()) {
        int a, b;
        stream >> a;
        stream.ignore(1);
        stream >> b;
        rational = Rational(a, b);
    }
    else stream.setstate(ios::failbit);
    return stream;
}


bool operator < (const Rational& lhs, const Rational& rhs) {
    return (lhs - rhs).Numerator() < 0;
}
*/

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
                 const string& hint)
{
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " hint: " << hint;
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (runtime_error& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

void Tests()
{
    {
        Rational r;
        Assert((r.Numerator() == 0) && (r.Denominator() == 1), "По умолчанию дробь: 0 / 1");
    }

    {
        Rational r(3, 2);
        Assert((r.Numerator() == 3) && (r.Denominator() == 2), "");
    }

    {
        Rational r(10, 5);
        Assert((r.Numerator() == 2) && (r.Denominator() == 1), "");
    }

    {
        Rational r(-1, 3);
        Assert((r.Numerator() == -1) && (r.Denominator() == 3), "");
    }

    {
        Rational r(1, -3);
        Assert((r.Numerator() == -1) && (r.Denominator() == 3), "");
    }

    {
        Rational r(3, -9);
        Assert((r.Numerator() == -1) && (r.Denominator() == 3), "");
    }

    {
        Rational r(-3, -3);
        Assert((r.Numerator() == 1) && (r.Denominator() == 1), "");
    }

    {
        Rational r(0, 2);
        Assert((r.Numerator() == 0) && (r.Denominator() == 1), "");
    }

}




int main() {
    TestRunner runner;
    runner.RunTest(Tests, "Tests");
    return 0;
}