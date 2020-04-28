#include <iostream>
#include <vector>

using namespace std;


int main() {
    int N;
    cin >> N;
    vector<int64_t> data(N);
    for (int i = 0; i < N; ++i) {
        cin >> data[i];
    }

    int64_t avg = 0;
    for(auto i : data)
        avg += i;
    avg /= static_cast<int64_t>(data.size());
    int K = 0;
    vector<int64_t> data2;
    for (int64_t i = 0; i < static_cast<int64_t>(data.size()); ++i)
        if (data[i] > avg) {
            K++;
            data2.push_back(i);
        }
    cout << K << endl;
    for (auto i : data2)
        cout << i << ' ';
    return 0;
}