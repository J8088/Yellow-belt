#include <iostream>
#include <algorithm>
#include <stack>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
using namespace std;

bool upper_priority(char prev_oper, char next_oper)
{
    return (((prev_oper == '+') || (prev_oper == '-'))
            && ((next_oper == '*') || (next_oper == '/')));
}

string GetExpression(const vector<int>& numbers, const vector<char>& operations, int count1) {
    stringstream result;
    auto count_operations = operations.size();
    for (int k = 0; k < count1; ++k)
        result << '(';
    if (count_operations == 0) {
        result << numbers[0];
        return result.str();
    }
    if (count_operations == 1) {
        result << numbers[0] << ' ' << operations[0] << ' ' << numbers[1];
        return result.str();
    }
    result << numbers[0] << ' ';
    int count = 0;
    for (int i = 0; i < count_operations; ++i) {
        result << operations[i] << " " << numbers[i + 1];
        if (i + 1 != count_operations) {
            if (upper_priority(operations[i], operations[i + 1])) {
                count++;
                result << ')';
            }
        }
        result << ' ';
    }
    return result.str();
}


int main()
{
    int x;
    uint N;
    cin >> x;
    cin >> N;
    vector<char> operations(N);
    vector<int> numbers(N + 1);
    numbers[0] = x;
    char operation;
    int number, count = 0;
    for (int i = 0; i < N; ++i) {
        cin >> operation >> number;
        numbers[i + 1] = number;
        operations[i] = operation;
        if ((i > 0) && ( upper_priority(operations[i - 1], operations[i])))
            count++;
    }
    string result = GetExpression(numbers, operations, count);
    cout << result << endl;
    return 0;
}
