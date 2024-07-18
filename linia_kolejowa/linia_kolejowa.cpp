#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <stack>
#include <algorithm>



using namespace std;

typedef struct rzadanie {
    long long start;
    long long end;
    long long t;
    long long id;
    long long count;
} rzadanie;



set<tuple<int, int, int>> rzadania_set;

set<int> wazne_punkty_set;

class AVL_count_greater {
    private: 
        struct node {
            long long val;
            long long count;
            long long subtree_size;
            long long height;
            node* left;
            node* right;
        };
        node* root;
        long long height(node* n) {
            if (n == nullptr) {
                return 0;
            }
            return n->height;
        }
        long long count(node* n) {
            if (n == nullptr) {
                return 0;
            }
            return n->count;
        }
        long long subtree_size(node* n) {
            if (n == nullptr) {
                return 0;
            }
            return n->subtree_size;
        }
        void update(node* n) {
            n->height = max(height(n->left), height(n->right)) + 1;
            //n->count = count(n->left) + count(n->right) + 1;
            n->subtree_size = subtree_size(n->left) + subtree_size(n->right) + n->count;
        }
        node* right_rotate(node* n) {
            node* x = n->left;
            node* T2 = x->right;
            x->right = n;
            n->left = T2;
            update(n);
            update(x);
            return x;
        }
        node* left_rotate(node* n) {
            node* x = n->right;
            node* T2 = x->left;
            x->left = n;
            n->right = T2;
            update(n);
            update(x);
            return x;
        }
        node* insert(node* n, long long x, long long count) {
            if (n == nullptr) {
                node* new_node = new node;
                new_node->val = x;
                new_node->count = count;
                new_node->subtree_size = count;
                new_node->height = 1;
                new_node->left = nullptr;
                new_node->right = nullptr;
                return new_node;
            }
            if (x < n->val) { // wstawiamy do lewego poddrzewa
                n->left = insert(n->left, x, count);
            } else if (x > n->val) { // wstawiamy do prawego poddrzewa
                n->right = insert(n->right, x, count);
            } else { // znalezlismy miejsce
                n->count += count;
                n->subtree_size += count;
                return n;
            }
            update(n);
            long long balance = height(n->left) - height(n->right);
            if (balance > 1 && x < n->left->val) {
                return right_rotate(n);
            }
            if (balance < -1 && x > n->right->val) {
                return left_rotate(n);
            }
            if (balance > 1 && x > n->left->val) {
                n->left = left_rotate(n->left);
                return right_rotate(n);
            }
            if (balance < -1 && x < n->right->val) {
                n->right = right_rotate(n->right);
                return left_rotate(n);
            }
            return n;
        }
        node* remove(node* n, long long x, long long count) {
            if (n == nullptr) {
                return n;
            }
            n->subtree_size -= count;
            if (x < n->val) {
                n->left = remove(n->left, x, count);
            } else if (x > n->val) {
                n->right = remove(n->right, x, count);
            } else {
                if (n->count > count) {
                    n->count -= count;
                    return n;
                } else if ( (n->left == nullptr) || (n->right == nullptr) ) { // scierzka z max jednym synem
                    node* temp = n->left ? n->left : n->right;
                    if (temp == nullptr) {
                        temp = n;
                        n = nullptr;
                    } else {
                        *n = *temp;
                    }
                    delete temp;
                } else { // sciezka z dwoma synami
                    node* temp = n->right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    n->val = temp->val;
                    n->count = temp->count;
                    n->right = remove(n->right, temp->val, temp->count);
                }
            }
            if (n == nullptr) {
                return n;
            }
            update(n);
            long long balance = height(n->left) - height(n->right);
            if (balance > 1 && height(n->left->left) - height(n->left->right) >= 0) {
                return right_rotate(n);
            }
            if (balance > 1 && height(n->left->left) - height(n->left->right) < 0) {
                n->left = left_rotate(n->left);
                return right_rotate(n);
            }
            if (balance < -1 && height(n->right->left) - height(n->right->right) <= 0) {
                return left_rotate(n);
            }
            if (balance < -1 && height(n->right->left) - height(n->right->right) > 0) {
                n->right = right_rotate(n->right);
                return left_rotate(n);
            }
            return n;
        }

        long long count_greater(node* n, long long x) {
            if (n == nullptr) {
                return 0;
            }
            if (n->val <= x) {
                return count_greater(n->right, x);
            }
            return subtree_size(n->right) + count_greater(n->left, x) + n->count;
        }

    public:
        AVL_count_greater() {
            root = nullptr;
        }
        ~AVL_count_greater() {
            delete root;
        }
        void insert(long long x, long long count) {
            root = insert(root, x, count);
        }
        void remove(long long x, long long count) {
            root = remove(root, x, count);
        }
        long long count_greater(long long x) {
            return count_greater(root, x);
        }
        void print() {
            // BFS through tree and prlong long nodes
            if (root == nullptr) {
                return;
            }
            vector<node*> q;
            q.push_back(root);
            while (!q.empty()) {
                node* n = q.front();
                q.erase(q.begin());
                cout <<"value: " << n->val << " count " << n->count << " height " << n->height << "subtree size " << n->subtree_size <<
                " lsyn val: " << (n->left ? n->left->val : -1) << " psyn val: " << (n->right ? n->right->val : -1) << "\n";
                if (n->left != nullptr) {
                    q.push_back(n->left);
                }
                if (n->right != nullptr) {
                    q.push_back(n->right);
                }
            }
            cout << "####################" << endl;
        }
};



int main()
{
    map<tuple<int, int, int>, rzadanie*> rzadania = map<tuple<int, int, int>, rzadanie*>();

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n , k;
    cin >> n >> k;
    //stack<rzadanie> s;
    for (long long i = 0; i < n; i++) {
        long long a, b, t;
        cin >> a >> b >> t;
        tuple<int, int, int> tup = make_tuple(a, b, t);
        if (rzadania_set.find(tup) == rzadania_set.end()) {
            rzadanie* r = new rzadanie;
            r->start = a;
            r->end = b;
            r->t = t;
            r->id = i;
            r->count = 1;
            rzadania[tup] = r;
            rzadania_set.insert(tup);
            wazne_punkty_set.insert(a);
            wazne_punkty_set.insert(b);
        }
        else {
            rzadania[tup]->count++;
        }
    }

    //return 0;

    vector<int> wazne_punkty;
    wazne_punkty.reserve(wazne_punkty_set.size());
    for (auto it = wazne_punkty_set.begin(); it != wazne_punkty_set.end(); it++) {
        wazne_punkty.push_back(*it);
    }
    sort(wazne_punkty.begin(), wazne_punkty.end());  //O(nlogn)
    //prlong long wazne_punkty
    /*for (long long i = 0; i < wazne_punkty.size(); i++) {
        cout << wazne_punkty[i] << " ";
    } cout << endl;*/
    //return 0;
    vector<rzadanie*> rzadania_by_start, rzadania_by_end;
    rzadania_by_start.reserve(rzadania.size());
    rzadania_by_end.reserve(rzadania.size());
    for (auto it = rzadania.begin(); it != rzadania.end(); it++) {
        rzadania_by_start.push_back(it->second);
        rzadania_by_end.push_back(it->second);
    }
    sort(rzadania_by_start.begin(), rzadania_by_start.end(), [](rzadanie* a, rzadanie* b) {return a->start < b->start; }); //O(nlogn)
    sort(rzadania_by_end.begin(), rzadania_by_end.end(), [](rzadanie* a, rzadanie* b) {return a->end < b->end; }); //O(nlogn)

    //vector<stack<rzadanie*>> poczatki, konce;
    //poczatki.resize(wazne_punkty.size());
    //konce.resize(wazne_punkty.size());
    //return 0;
    long long jp = 0, jk = 0;
    for (long long i = 0; i < wazne_punkty.size(); i++) {
        /*while (jp < rzadania_by_start.size() && rzadania_by_start[jp]->start <= wazne_punkty[i]) {
            poczatki[i].push(rzadania_by_start[jp]);
            jp++;
        }*/
        /*while (jk < rzadania_by_end.size() && rzadania_by_end[jk]->end < wazne_punkty[i]) {
            konce[i].push(rzadania_by_end[jk]);
            jk++;
        }*/
    }

    AVL_count_greater avl;
    long long count = 0; // liczba par do wypisania
    char c;
    jp = 0, jk = 0;
    
    for (long long i = 0; i < wazne_punkty.size(); i++) { 

        while (jk < rzadania_by_end.size() && rzadania_by_end[jk]->end < wazne_punkty[i]) {
            //rzadanie *r = konce[i].top();
            //konce[i].pop();
            rzadanie *r = rzadania_by_end[jk];
            jk++;
            avl.remove(r->t, r->count);
            //printf("avl after remove %d\n", r->t);
            //avl.print();
            //cin >> c;
        }
        
        while (jp < rzadania_by_start.size() && rzadania_by_start[jp]->start <= wazne_punkty[i]) {
            //rzadanie *r = poczatki[i].top();
            //poczatki[i].pop();
            rzadanie *r = rzadania_by_start[jp];
            jp++;
            long long inc = avl.count_greater((k + 1) < r->t ? r->t - k - 1 : 0) - avl.count_greater(r->t + k); 
            if (inc > 0) {
                //cout << i << " " << r->id << endl;
            }
            avl.insert(r->t, r->count);
            count += inc;
            if (r->count > 1) {
                count += (r->count * (r->count - 1)) / 2;
            }

            //printf("i = %d, r->t = %d, r->count = %d\n", i, r->t, r->count);

            //printf("avl after insert %d\n", r->t);
            //avl.print();
            //cin >> c;
        }

        
        
    }

    cout << count << endl;
    //printf("hi\n");

    return 0;

}