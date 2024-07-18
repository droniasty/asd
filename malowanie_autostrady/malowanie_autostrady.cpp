#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

#define przedzial pair <uint32_t, uint32_t>
# define BIALY 0
# define CZARNY 1
# define SZARY 2


class IntervalTree {
    private:
        uint32_t size;

        struct Node {
            przedzial przedz;
            uint32_t pomalowany = CZARNY;
            uint32_t pomalowane = 0;
            Node *left, *right;

            Node (przedzial przedz){
                this->przedz = przedz;
                if (przedz.first != przedz.second) {
                    przedzial leftPrzedz = make_pair(przedz.first, (przedz.first + przedz.second) / 2);
                    this->left = new Node(leftPrzedz);
                    przedzial rightPrzedz = make_pair((przedz.first + przedz.second) / 2 + 1, przedz.second);
                    this->right = new Node(rightPrzedz);
                } else {
                    this->left = nullptr;
                    this->right = nullptr;
                }
            }

            Node() : przedz(), pomalowany(CZARNY), pomalowane(0), left(nullptr), right(nullptr) {
                // Additional initialization if needed
            }

            void paint(uint32_t a, uint32_t b) {
                if (b < przedz.first || a > przedz.second) return;
                if (pomalowany == BIALY) return;
                if (a <= przedz.first && przedz.second <= b) {
                    pomalowany = BIALY;
                    pomalowane = przedz.second - przedz.first + 1;
                } else if (przedz.first <= b && a <= przedz.second) {
                    if (pomalowany == CZARNY) {
                        if (a > przedz.first) {
                            left->unpaint(przedz.first, a-1);
                        }
                        if (b < (przedz.first + przedz.second) / 2) {
                            left->unpaint(b+1, (przedz.first + przedz.second) / 2);
                        }
                        if (a > (przedz.first + przedz.second) / 2 + 1) {
                            right->unpaint((przedz.first + przedz.second) / 2 + 1, a-1);
                        }
                        if (b < przedz.second) {
                            right->unpaint(b+1,przedz.second);
                        }
                    }
                    pomalowany = SZARY;
                    if (left != nullptr) {
                        left->paint(a, b);
                    }
                    if (right != nullptr) {
                        right->paint(a, b);
                    }
                    pomalowane = (left != nullptr ? left->pomalowane : 0) + (right != nullptr ? right->pomalowane : 0);
                }
            }

            void unpaint(uint32_t a, uint32_t b) {
                if (b < przedz.first || a > przedz.second) return;
                if (pomalowany == CZARNY) return;
                if (a <= przedz.first && przedz.second <= b) {
                    pomalowany = CZARNY;
                    pomalowane = 0;
                } else if (przedz.first <= b && a <= przedz.second) {
                    if (pomalowany == BIALY) {
                         if (a > przedz.first) {
                            left->paint(przedz.first, a-1);
                        }
                        if (b < (przedz.first + przedz.second) / 2) {
                            left->paint(b+1, (przedz.first + przedz.second) / 2);
                        }
                        if (a > (przedz.first + przedz.second) / 2 + 1) {
                            right->paint((przedz.first + przedz.second) / 2 + 1, a-1);
                        }
                        if (b < przedz.second) {
                            right->paint(b+1,przedz.second);
                        }
                    }
                    pomalowany = SZARY;
                    if (left != nullptr) {
                        left->unpaint(a, b);
                    }
                    if (right != nullptr) {
                        right->unpaint(a, b);
                    }
                    pomalowane = (left != nullptr ? left->pomalowane : 0) + (right != nullptr ? right->pomalowane : 0);
                }
            }

        };

        Node root;
    
    public:

        
        
        IntervalTree(uint32_t n) {
            this->size = 1;
            while (this->size < n) this->size *= 2;
            this->root = Node({1, this->size});
        }

        void pait(uint32_t a, uint32_t b) {
            root.paint(a,b);
        }

        void unpaint(uint32_t a, uint32_t b) {
            root.unpaint(a,b);
        }

        uint32_t getPainted () {
            return root.pomalowane;
        }
};


int main() {
    uint32_t n, m;
    cin >> n >> m;
    IntervalTree tree = IntervalTree(n);
    for (uint32_t i = 0; i < m; i++) {
        uint32_t a, b;
        char c;
        cin >> a >> b >> c;
        if (c == 'B') {
            tree.pait(a, b);
        } else if (c == 'C') {
            tree.unpaint(a, b);
        }
        cout << tree.getPainted() << endl;
    }
    return 0;
}