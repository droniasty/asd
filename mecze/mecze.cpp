#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    uint32_t n, m;
    std::cin >> n >> m;
    vector<uint64_t> zawodnicy(n, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n/2; j++) {
            uint32_t a;
            std::cin >> a;
            // set i-th bit of zawodnicy[a] to 1
            zawodnicy[a - 1] |= (1LL << i);
        }
        for (int j = 0; j < n/2; j++) {
            uint32_t a;
            std::cin >> a;
        }

    }
    set<uint64_t> unikalne;
    for (int i = 0; i < n; i++) {
        if (unikalne.find(zawodnicy[i]) == unikalne.end()) {
            unikalne.insert(zawodnicy[i]);
        } else {
            cout << "NIE\n";
            return 0;
        }
    }
    cout << "TAK\n";
    return 0;

}