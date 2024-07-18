#include <iostream>
#include <vector>


using namespace std;
# define miliard 1000000000

std::vector<uint32_t> ciag;

int main () {
    uint32_t n;
    cin >> n;
    ciag.resize(n);
    for (uint32_t i = 0; i < n; i++) {
        cin >> ciag[i];
    }
    if (n <= 1) {
        cout << 1 << endl;
        return 0;
    }
    uint32_t left[n][n];
    uint32_t right[n][n];
    for (uint32_t i = 0; i < n; i++) {
        for (uint32_t j = 0; j < n; j++) {
            left[i][j] = 0;
            right[i][j] = 0;
        }
    }
    for (uint32_t i = 0; i < n; i++) {
        left[i][i] = 1;
        right[i][i] = 1;
    }
    for (uint32_t i = 0; i < n - 1; i++) {
        left[i][i + 1] = (ciag[i] < ciag[i + 1]);
        right[i][i + 1] = (ciag[i] < ciag[i + 1]);
    }
    for (uint32_t j = 2; j < n; j++) {
        for (uint32_t i = j - 2; i < n; i--) { // overflow lamie dozr pentli
            left[i][i + j] = 0;
            right[i][i + j] = 0;
            if (ciag[i] < ciag[i + 1]) {
                left[i][j] += left[i + 1][j];
            }
            if (ciag[i] < ciag[j]) {
                left[i][j] += right[i+1][j];
            }
            left[i][j] %= miliard;
            if (ciag[j] > ciag[i]) {
                right[i][j] += left[i][j - 1];
            }
            if (ciag[j] > ciag[j - 1]) {
                right[i][j] += right[i][j - 1];
            }
            right[i][j] %= miliard;
        }
    }
    //cout left and right
    /*for (uint32_t i = 0; i < n; i++) {
        for (uint32_t j = 0; j < n; j++) {
            cout << left[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (uint32_t i = 0; i < n; i++) {
        for (uint32_t j = 0; j < n; j++) {
            cout << right[i][j] << " ";
        }
        cout << endl;
    }
    cout << left[0][n - 1] << " " << right[0][n - 1] << endl;*/
    cout << (left[0][n - 1] + right[0][n - 1]) % miliard << endl;
    return 0;

}