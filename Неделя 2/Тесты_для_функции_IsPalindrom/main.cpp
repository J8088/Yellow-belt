#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
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
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
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
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
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

bool IsPalindrom(string s) {
    for (size_t i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
void Tests()
{
    {
        Assert(IsPalindrom("madam"), " madam - is palindrom! ");
        Assert(IsPalindrom("level"), " level - is palindrom! ");
        Assert(IsPalindrom("wasitacaroracatisaw"), " wasitacaroracatisaw - is palindrom! ");
        Assert(IsPalindrom(""), " empty_string - is palindrom! ");
        Assert(IsPalindrom("m"), " m - is palindrom! ");
        Assert(IsPalindrom("fgh hgf"), " fgh hgf - is palindrom! ");
        Assert(IsPalindrom(" fgh hgf "), "  fgh hgf  - is palindrom! ");
        Assert(IsPalindrom("mm"), " mm  - is palindrom! ");
        Assert(IsPalindrom(" "), "    - is palindrom! ");
        Assert(IsPalindrom("  fgh   hgf  "), "   fgh   hgf   - is palindrom! ");
        Assert(IsPalindrom("asddsa"), " asddsa - is palindrom! ");
        Assert(IsPalindrom("asdsa"), " asdsa - is palindrom! ");
        Assert(IsPalindrom(" a v aa / r/ /r / aa v a "), "  a v aa / r/ /r / aa v a  - is palindrom! ");
        Assert(IsPalindrom("aaaaaaaaaaaa"), " aaaaaaaaaaaa - is palindrom! ");
        Assert(IsPalindrom("hhh"), " hhh - is palindrom! ");
        Assert(IsPalindrom("           "), "             - is palindrom! ");
        Assert(IsPalindrom("--g-g-g-g--"), "             - is palindrom! ");
        AssertEqual(IsPalindrom("madam"), 1);
        AssertEqual(IsPalindrom("lool"), 1);
        AssertEqual(IsPalindrom("o"), 1);
        AssertEqual(IsPalindrom(""), 1);
        AssertEqual(IsPalindrom(" "), 1);
        AssertEqual(IsPalindrom("  "), 1);
        AssertEqual(IsPalindrom("top pot"), 1);
        AssertEqual(IsPalindrom("o lol o"), 1);
        AssertEqual(IsPalindrom(" olo "), 1);
        AssertEqual(IsPalindrom("olol"), 0);
        AssertEqual(IsPalindrom("motor"), 0);
        AssertEqual(IsPalindrom("topo gun"), 0);
        AssertEqual(IsPalindrom("olol "), 0);
        AssertEqual(IsPalindrom(" lol"), 0);
        AssertEqual(IsPalindrom("olo"+'\n'), 1);
        AssertEqual(IsPalindrom("////7  7                   7  7////"), 1);
        AssertEqual(IsPalindrom("- - - -"), 1);
        AssertEqual(IsPalindrom("qwertyuiop[]][poiuytrewq"), 1);
        AssertEqual(IsPalindrom("abarba"), 0);
        AssertEqual(IsPalindrom("  g f d  "), 0);
        AssertEqual(IsPalindrom("  3e"), 0);
        AssertEqual(IsPalindrom("3e"), 0);

    }
}

int main() {
    TestRunner runner;
    runner.RunTest(Tests, "Tests");
    return 0;
}