#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void PrintRange(vector<int> v)
{
    for (int i : v)
        cout << i << " ";
    cout << endl;
}

void PrintReversedVector(vector<vector<int>> vv)
{
    reverse(vv.begin(), vv.end());
    for (auto i : vv)
        PrintRange(i);
}


int main() {
    int N;
    cin >> N;
    vector<int> range;
    for (int i = 1; i < N + 1; ++i)
        range.push_back(i);
    vector<vector<int>> temp;
    do
    {
        temp.push_back(range);
    }
    while (next_permutation(range.begin(), range.end()));
    PrintReversedVector(temp);

    return 0;
}

