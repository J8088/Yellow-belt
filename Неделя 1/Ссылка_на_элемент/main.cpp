#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <exception>
#include <string>
using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K,V>& m, K k)
{
    try {
        return m.at(k);
    }
    catch (exception& ex)
    {
        throw runtime_error("");
    }
}


int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 4);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}
