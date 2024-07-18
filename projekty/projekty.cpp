#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct graph {
    uint32_t waga;
    uint32_t ile_potrzeba = 0;
    uint32_t id;

    bool operator<(graph const& g2) const {
        return waga > g2.waga;
    }

    //graph(uint32_t waga, uint32_t id) : waga(waga), ile_potrzeba(0), id(id) {}
};


vector <struct graph> graf;
vector<vector<uint32_t>> to, from;

int main () {

    ios_base::sync_with_stdio(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    graf.resize(n);
    to.resize(n);
    from.resize(n);
    for (uint32_t i = 0; i < n; i++) {
        uint32_t j;
        cin >> j;
        graf[i].id = i;
        graf[i].ile_potrzeba = 0;
        graf[i].waga = j;
    }
    for (uint32_t i = 0; i < m; i++) {
        uint32_t a, b;
        cin >> a >> b;
        a--; b--;
        from[b].push_back(a);
        graf[a].ile_potrzeba++;
        to[a].push_back(b);
    }
    priority_queue<struct graph> Q;
    for (uint32_t i = 0; i < n; i++) {
        //cout << i+1 << " " << graf[i].ile_potrzeba << endl;
        if(graf[i].ile_potrzeba == 0) {
            Q.push(graf[i]);
        }
    }
    //for (uint32_t i = 0; i < n; i++) cout << 
    //cout << endl << Q.size();
    //return 0;
    uint32_t ile_wybrano = 0;
    uint32_t maks = 0;
    while (ile_wybrano < k)
    {
        //cout << "hi\n";
        struct graph v = Q.top();  
        Q.pop();
        //cout << v.id << " " << v.waga << endl;
        ile_wybrano++;
        if (v.waga > maks) {
            maks = v.waga;
        }
        for (uint32_t i : from[v.id]) {
            graf[i].ile_potrzeba--;
            if (graf[i].ile_potrzeba == 0) {
                Q.push(graf[i]);
            }
        }

    }
    
    cout << maks;
    return 0;

}