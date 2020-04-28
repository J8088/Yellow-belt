#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
    auto border = find_if(numbers.begin(), numbers.end(), [](const int& i){ return i < 0; });
    auto i = border;
    while (i != numbers.begin())
    {
        i--;
        cout << *i << ' ';
    }
    cout << endl;
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  PrintVectorPart({6, 1, 8, 5, 4});
  return 0;
}
