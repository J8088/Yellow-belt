#include <iostream>
#include "sum_reverse_sort.h"

using namespace std;


int main() {
    cout << Sum(5, 6) << endl;
    cout << Reverse("abcdef") << endl;
    vector<int> v = {1, 2, 3,2, 6, 4};
    Sort(v);
    for (const int& i : v)
        cout << i << " ";
    return 0;
}