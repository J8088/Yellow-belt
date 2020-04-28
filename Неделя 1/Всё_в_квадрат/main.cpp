#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>
using namespace std;


template <typename  T> vector<T> Sqr(const vector<T>& v);
template <typename  First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);
template <typename T> T Sqr(const T& x);

template <typename  T>
vector<T> Sqr(const vector<T>& v)
{
    vector<T> res = v;
    for (int i = 0; i < v.size(); ++i) {
        res[i] = Sqr(v[i]);
    }
    return res;
}

template <typename  First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p)

{
    pair<First, Second> res;
    res.first = Sqr(p.first);
    res.second = Sqr(p.second);
    return res;

}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m)
{
    map<Key, Value> res;
    for (const auto& i : m) {
        res[i.first] = Sqr(i.second);
    }
    return res;
};

template <typename T>
T Sqr(const T& x)
{
    return x * x;
}



int main()
{
// Пример вызова функции
vector<int> v = {1, 2, 3};
cout << "vector:";
for (int x : Sqr(v)) {
  cout << ' ' << x;
}
cout << endl;

map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
};
cout << "map of pairs:" << endl;
for (const auto& x : Sqr(map_of_pairs)) {
  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}
    return 0;
}