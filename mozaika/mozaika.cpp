#include <iostream>
#include <utility>
#include <vector>

std::vector <uint64_t> pytania;
std::vector <uint64_t> wyniki;


void dla_k_1(uint64_t n) {
    for (uint64_t i = 0; i < n; ++i) {
        // cout 2^(pytania[i])
        wyniki[i] = (1 << (pytania[i]));
    }
    for (uint64_t i = 0; i < n; ++i) {
        std::cout << wyniki[pytania[i] - 1] << " ";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    uint64_t n, k;
    std::cin >> n >> k;
    //std::vector <uint64_t> pytania(n);
    pytania.resize(n);
    //std::vector <uint64_t> wyniki(n,0);
    wyniki.resize(n, 0);
    // znajdujemy najwieksze pytanie
    uint64_t max_pytanie = 0;
    for (uint64_t i = 0; i < n; ++i) {
        std::cin >> pytania[i];
        if (pytania[i] > max_pytanie) {
            max_pytanie = pytania[i];
        }
    }
    
    k++;
    //std::vector<std::vector<uint64_t>> ile_mozaiek(k, std::vector<uint64_t>(max_pytanie, 0));
    std::vector <uint64_t> ile_mozaiek(k);
    std::vector <uint64_t> prev_ile_mozaiek(k);
    for (uint64_t i = 0; i < k; ++i) {
        ile_mozaiek[i] = 1;
    }
    wyniki[0] = k;
    for (uint64_t i = 1; i < max_pytanie; ++i) {
        std::swap(ile_mozaiek, prev_ile_mozaiek);
        for (uint64_t j = 0; j < k; ++j) {
            if (j == 0) {
                ile_mozaiek[j] = prev_ile_mozaiek[j] + prev_ile_mozaiek[j + 1];
                ile_mozaiek[j] %= 1000000000;
            } else if (j == k - 1) {
                ile_mozaiek[j] = prev_ile_mozaiek[j - 1] + prev_ile_mozaiek[j];
                ile_mozaiek[j] %= 1000000000;
            } else {
                ile_mozaiek[j] = prev_ile_mozaiek[j - 1] + prev_ile_mozaiek[j] + prev_ile_mozaiek[j + 1];
                ile_mozaiek[j] %= 1000000000;
            }
        }
        for (uint64_t j = 0; j < k; ++j) {
            wyniki[i] += ile_mozaiek[j];
            wyniki[i] %= 1000000000;
        }
    }
    for (uint64_t i = 0; i < n; ++i) {
        std::cout << wyniki[pytania[i] - 1] << " ";
    }
    return 0;
}