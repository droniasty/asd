#include <iostream>
#include <cstdlib>



using namespace std;

int main () {
    ios_base::sync_with_stdio(0);

    string tap;
    cin >> tap;
    char previous_char = '*'; // poprzedni istotny znak
    int pidx = 0; // index poprzedniego istotnego znaku
    int odl = tap.size() - 1; // odleglosc miedzy najblizszymi istotnymi znakami
    for (size_t i = 0; i < tap.size(); i++) {
        if (tap[i] != '*') {
            if (previous_char != '*' && tap[i] != previous_char) {
                odl = std::min(odl, (int)i - pidx - 1);
            }
            pidx = i;
            previous_char = tap[i];
        }
    }


    cout << tap.size() - odl << endl; // wynikiem jest suma odleglosci najblizszych istotnyc znakow od krawedzi tapety
    return 0;
}