#include <iostream>
#include <algorithm>
#include <stack>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
using namespace std;



string GetExpression(const vector<int>& numbers, const vector<char>& operations) {
    stringstream result;
    auto count_operations = operations.size();
    auto count_numbers = numbers.size();
    for (int i = 0; i < count_operations; ++i)
        result << "(";
    result << numbers[0];
    for (int i = 1; i < count_numbers; ++i) {
        result << ") ";
        char operation = operations[i - 1];
        int number = numbers[i];
        result << operation;
        result << " ";
        result << number;
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
    int number;
    for (int i = 0; i < N; ++i) {
        cin >> operation >> number;
        numbers[i + 1] = number;
        operations[i] = operation;
    }
    string result = GetExpression(numbers, operations);
    cout << result << endl;
    return 0;
}
