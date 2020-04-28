#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto it = begin(s);
    while (it < end(s))
    {
        auto space_it = find_if(it, end(s), [](const char &c) { return c == ' '; });
        string word = {it, space_it};
        result.push_back(word);
        it = space_it + 1;
    }
    return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}
