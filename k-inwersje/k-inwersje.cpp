#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

const int mld = 1000*1000*1000;

class count_tree{
    private:
        typedef struct node {
            uint64_t val; // suma na przedziale
            uint64_t mini; // lewy koniec przedzialu
            uint64_t maxi;  // prawy koniec przedzialu
        } node;
        vector <node> tree;
        uint64_t n;
        uint64_t left (uint64_t v) {return v << 1;}
        uint64_t right (uint64_t v) {return (v << 1) + 1;}
        uint64_t parent (uint64_t v) {return v >> 1;}
        void update (uint64_t v) {
            //tree[v].val = tree[left(v)].val + tree[right(v)].val;
            tree[v].mini = tree[left(v)].mini;
            tree[v].maxi = tree[right(v)].maxi;
        }
        
    public:
        count_tree (uint64_t n) {
            //this->n = n;
            // set this->n to the smallest power of 2 greater than n
            this->n = 1;
            while (this->n < n) {
                this->n <<= 1;
            }
            tree.resize(2*this->n);
            for (uint64_t i = 0; i < 2*this->n; i++) {
                tree[i].val = 0;
                tree[i].mini = 0;
                tree[i].maxi = 0;
            }
            for (uint64_t i = 0; i < (this->n); i++) {
                tree[(this->n)+i].val = 0;
                tree[(this->n)+i].mini = i;
                tree[(this->n)+i].maxi = i;
            }
            for (uint64_t i = (this->n)-1; i > 0; i--) {
                update(i);
            }
            // print tree
            /*for (uint64_t i = 0; i < 2*(this->n); i++) {
                cout << "i: " << i << " val: " << tree[i].val << " mini: " << tree[i].mini << " maxi: " << tree[i].maxi << endl;
            }*/
        }
        uint64_t insert (uint64_t poz, uint64_t v) {
            uint w = 1;
            uint64_t res = 0;
            while (w < (this->n)) {
                tree[w].val += v;
                tree[w].val %= mld;
                //cout << "w: " << w << " val: " << tree[w].val << endl;
                // if poz closer to mini go left else go right
                //cout << "poz: " << poz  << " maxi: " << (tree[left(w)].maxi) << endl;
                if (poz <= (tree[left(w)].maxi)) {
                    w = left(w);
                    // increment res by the value of right
                    //res += tree[right(w)].val;
                } else {
                    res += tree[left(w)].val;
                    res %= mld;
                    w = right(w);
                }
            }
            tree[w].val += v;
            tree[w].val %= mld;
            //cout << "res: " << res << endl;
            return res;
        }

        uint64_t get_sum() {
            return tree[1].val;
        }

};
vector <vector <uint64_t> > T;


uint64_t n,k;

int main()
{
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    T.resize(k, vector <uint64_t> (n, 0));
    uint64_t arr[n];
    for (uint64_t i = 0; i < n; i++) {
        uint64_t a;
        cin >> a;
        arr[i] = a - 1;
        T[0][i] = 1;
    }
    for (uint64_t i = 1; i < k; i++) {
        count_tree tree(n);
        for (uint64_t j = 1; j <= n; j++) {
            uint64_t smaller = tree.insert(arr[n-j], T[i-1][n-j]);
            T[i][n-j] = smaller;
        }
    }
    uint64_t wynik = 0;
    for (uint64_t i = 0; i < n; i++) {
        wynik += T[k-1][i];
        wynik %= mld;
    }
    // cout T
    /*for (uint64_t i = 0; i < k; i++) {
         for (uint64_t j = 0; j < n; j++) {
            cout << T[i][j] << " ";
         }
         cout << endl;
    }*/
    //cout << endl;
    cout << wynik % mld << endl;
    return 0;
}