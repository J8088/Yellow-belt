#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T>

void Print(vector<T> v)
{
    for (auto i : v)
        cout << i << " ";
    cout << endl;
}





template <typename RandomIt>

void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    int count = range_end - range_begin;
    if (count < 2)
        return;
    vector<typename RandomIt::value_type> v(range_begin, range_end);
    RandomIt middle = v.begin() + count / 2;
    MergeSort(v.begin(), middle);
    MergeSort(middle, v.end());
    merge(v.begin(), middle, middle, v.end(), range_begin);
}


int main() {
    vector<int> v = {1, 3, 2, 0, 9, 6, 8, 9};
    MergeSort(v.begin(), v.end());
    Print(v);
    return 0;
}
