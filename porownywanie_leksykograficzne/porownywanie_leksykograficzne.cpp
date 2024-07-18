#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

int power_2(int n) {
    int res = 1;
    for (int i = 0; i < n; i++) {
        res *= 2;
    }
    return res;
}

vector<tuple<int, int, int>> bucket_sort_tuple_vector(vector<tuple<int, int, int>> v) {

}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    string slowo;
    cin >> slowo;
    // compute lg n
    int lgn = 0;
    while ((1 << lgn) < n) {
        lgn++;
    }
    if ((1 << lgn) > n) {
        lgn--;
    }
    //printf("lgn = %d\n", lgn);

    int nazwa[n][lgn + 1];
    for (int i = 0; i < n; i++) {
        nazwa[i][0] = slowo[i] - 'a';
    }
    // print nazwa
    /*for (int i = 0; i < n; i++) {
        //cout << nazwa[i][0] + 1 << " ";
        printf("%d ", nazwa[i][0]);
    }
    //cout << "\n";
    printf("\n");
    //getchar();
    printf("lgn = %d\n", lgn);*/

    for (int k = 0; k < lgn; k++) {
        //printf("k = %d\n", k);
        vector<tuple<int, int, int>> tymczasowa;
        int ile = n - (1 << (k + 1)) + 1;
        //printf("ile = %d\n", ile);
        tymczasowa.reserve(ile);
        //print tymczasowa begin and end
        //printf("% d %d\n", tymczasowa.begin(), tymczasowa.end());
        for (int i = 0; i < ile; i++) {
            //v.push_back(make_tuple(nazwa[i][j - 1], nazwa[(i + (1 << (j - 1))) % n][j - 1], i));
            //tymczasowa[i] = make_tuple(nazwa[i][k], nazwa[(i + (1 << (k))) % n][k], i);
            tymczasowa.push_back(make_tuple(nazwa[i][k], nazwa[(i + power_2(k)) % n][k], i));
            //printf("(%d, %d) ", get<0>(tymczasowa[i]), get<1>(tymczasowa[i]));
        } //printf("\n");
        //printf("tymczasowa %d %d\n", tymczasowa.begin(), tymczasowa.end());
        // reverse  tymczasowa
        //reverse(tymczasowa.begin(), tymczasowa.end());
        /*for (int i = 0; i < ile; i++) {
            printf("(%d, %d) ", get<0>(tymczasowa[i]), get<1>(tymczasowa[i]));
        } printf("\n");*/
        //tymczasowa = bucket_sort_tuple_vector(tymczasowa);
        sort(tymczasowa.begin(), tymczasowa.end(), [](const tuple<int, int, int> a , const tuple<int, int, int> b){return get<0>(a) < get<0>(b) || (get<0>(a) == get<0>(b) && get<1>(a) < get<1>(b));});
        /*for (int i = 0; i < ile; i++) {
            printf("(%d, %d) ", get<0>(tymczasowa[i]), get<1>(tymczasowa[i]));
        } printf("\n");*/
        
        int nr = -1;
        pair<int, int> poprzedni = make_pair(-1, -1);
        for (int i = 0; i < ile; i++) {
            if (get<0>(tymczasowa[i]) != poprzedni.first || get<1>(tymczasowa[i]) != poprzedni.second) {
                nr++;
                poprzedni = make_pair(get<0>(tymczasowa[i]), get<1>(tymczasowa[i]));
            }
            nazwa[get<2>(tymczasowa[i])][k+1] = nr;
        }
        /*for (int i = 0; i < n; i++) {
            //cout << nazwa[i][0] + 1 << " ";
            printf("%d ", nazwa[i][0]);
        }
        //cout << "\n";
        printf("\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", nazwa[i][k+1]);
        } printf("\n");*/
        
    }


    for (int i = 0; i < m; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a;
        --b;
        --c;
        --d;
        int dl = min(b - a + 1, d - c + 1);
        int k; 
        for (k = 0; (1 << (k + 1)) <= dl; k++);
        /*printf("k = %d\n", k);
        for (int i = 0; i < n; i++) {
            //cout << nazwa[i][0] + 1 << " ";
            printf("%d ", nazwa[i][0]);
        }
        //cout << "\n";
        printf("\n");*/
        if (nazwa[a][k] < nazwa[c][k]) {
            cout << "<\n";
        } else if (nazwa[a][k] > nazwa[c][k]) {
            cout << ">\n";
        } else {
            if (nazwa[a + dl - (1 << k)][k] < nazwa[c + dl - (1 << k)][k]) {
                cout << "<\n";
            } else if (nazwa[a + dl - (1 << k)][k] > nazwa[c + dl - (1 << k)][k]) {
                cout << ">\n";
            } else { // porownanie dlugosci
                //cout << "=\n";
                if (b - a == d - c) { 
                    cout << "=\n";
                } else if (b - a < d - c) {
                    cout << "<\n";
                } else {
                    cout << ">\n";
                }
            }
        }




    }
    return 0;

}