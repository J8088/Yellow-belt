#include <iostream>
#include <vector>

using namespace std;


int main() {
    uint64_t N, R;
    cin >> N >> R;
    uint64_t W, H, D;
    uint64_t M, SUM_M = 0;
    for (uint64_t i = 0; i < N; ++i) {
        cin >> W >> H >> D;
        M = W * H * D * R;
        SUM_M += M;
    }
    cout << SUM_M;
    return 0;
}