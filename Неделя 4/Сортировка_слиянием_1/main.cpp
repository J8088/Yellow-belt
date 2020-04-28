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
    if (count < 3)
        return;
    vector<typename RandomIt::value_type> v(range_begin, range_end);
    RandomIt part1 = v.begin() + count / 3;
    RandomIt part2 = v.begin() + 2 * count / 3;
    MergeSort(v.begin(), part1);
    MergeSort(part1, part2);
    MergeSort(part2, v.end());
    vector<typename RandomIt::value_type> temp;
    merge(v.begin(), part1, part1, part2, back_inserter(temp));
    merge(temp.begin(), temp.end(), part2, v.end(), range_begin);
}


int main() {
    vector<int> v = {1, 3, 2, 0, 9, 6, 8, 9};
    MergeSort(v.begin(), v.end());
    Print(v);
    return 0;
}
