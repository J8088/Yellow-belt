#include <iostream>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;

set<int>::const_iterator FindNearestElement( const set<int>& numbers, int border)
{
    auto upper_or_equal = numbers.lower_bound(border);
    if (upper_or_equal == numbers.begin())
        return upper_or_equal;
    if (upper_or_equal == numbers.end())
        return prev(numbers.end());
    auto under = prev(upper_or_equal);
    int un = *under;
    int up = *upper_or_equal;
    if ((up - border) < (border - un))
        return upper_or_equal;
    else
        return under;
}
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
