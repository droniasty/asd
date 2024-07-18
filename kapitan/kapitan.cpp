#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int n;

struct wyspa {
    int id;
    pair<int, int> wspolrzedne;
    set<int> sasiedzi;
    int weight;

    wyspa(int id_value, std::pair<int, int> wsp_value) : id(id_value), wspolrzedne(wsp_value), weight(2 * 1000000000) {}

    bool operator<(wyspa const& w) const {
        if (weight != w.weight) return weight < w.weight;
        else return id > w.id;
    }

};

struct compareByWeight {
    bool operator()(const wyspa *lhs, const wyspa *rhs) const {
        return lhs->weight < rhs->weight;
    }
};

vector<struct wyspa*> wyspy;

bool by_x (struct wyspa* a, struct wyspa* b) {
    return a->wspolrzedne.first < b->wspolrzedne.first;
}

bool by_y (struct wyspa* a, struct wyspa* b) {
    return a->wspolrzedne.second < b->wspolrzedne.second;
}

int distance (struct wyspa* a, struct wyspa* b) {
    return min(abs(a->wspolrzedne.first - b->wspolrzedne.first), abs(a->wspolrzedne.second - b->wspolrzedne.second));
}

vector<bool> odwiedzone;

struct ComparePairsBySecond {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
        return lhs.second > rhs.second; // Note the greater than for a min-heap behavior
    }
};

int main()
{
    using myPair = std::pair<int, int>;
    ios_base::sync_with_stdio(0);
    cin >> n;
    wyspy.resize(n);
    odwiedzone.resize(n, false);
    set<int> S;
    std::priority_queue<myPair, std::vector<myPair>, ComparePairsBySecond> Q;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        wyspy[i] = new wyspa(i, {a, b});
        if (i == 0)wyspy[i]->weight = 0;
        if (wyspy[0]->wspolrzedne.first == wyspy[i]->wspolrzedne.first || wyspy[0]->wspolrzedne.second == wyspy[i]->wspolrzedne.second) {
            wyspy[i]->weight = 0;
        }
        Q.push({i, wyspy[i]->weight });
    }
    
    //cout << Q.size() <<endl;
    
    vector<struct wyspa*> posortowane = wyspy;
    if (wyspy[0]->wspolrzedne.first == wyspy[n-1]->wspolrzedne.first || wyspy[0]->wspolrzedne.second == wyspy[n-1]->wspolrzedne.second) {
        cout << 0;
        return 0;
    }
    sort(posortowane.begin(), posortowane.end(), by_x);
    for (int i = 1; i < n; i++) {
        posortowane[i]->sasiedzi.insert(posortowane[i-1]->id);
        posortowane[i-1]->sasiedzi.insert(posortowane[i]->id);
    }
    sort(posortowane.begin(), posortowane.end(), by_y);
    for (int i = 1; i < n; i++) {
        posortowane[i]->sasiedzi.insert(posortowane[i-1]->id);
        posortowane[i-1]->sasiedzi.insert(posortowane[i]->id);
    }
    for (int i = 0; i < n; i++) {
        //cout << i+1 << ": ";
        //for (auto a : wyspy[i]->sasiedzi) cout << a + 1 << " ";
        //cout << endl;
    }
    
    
    for (uint32_t i = 0; i < n; i++) {
        
        myPair p;
        struct wyspa * u;
        do {
            p = Q.top();
            Q.pop();
            u = wyspy[p.first];
            //cout << u->id + 1 << " " << u->weight << endl;

        } while (odwiedzone[u->id]);
        odwiedzone[u->id] = true;
        for (int s : u->sasiedzi) {
            if (wyspy[s]->weight > u->weight + distance(u, wyspy[s])){
                wyspy[s]->weight = u->weight + distance(u, wyspy[s]);
                Q.push({wyspy[s]->id, wyspy[s]->weight});
            }
        }
    }
    cout << wyspy[n-1]->weight;
    
    return  0;
}