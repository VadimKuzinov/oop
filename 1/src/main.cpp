#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include <unordered_map>
#include "sprs.h"

struct PairHasher {
    template <typename U, typename V>
    size_t operator()(const std::pair<U, V>& pair) const {
        auto hashU = std::hash<U>{}(pair.first);
        auto hashV = std::hash<V>{}(pair.second);
        return hashU != hashV ? hashU ^ hashV : hashU;
    }
};


int main() {
    std::vector<std::tuple<std::size_t, std::size_t, long long>> arr;
    std::map<std::pair<std::size_t, std::size_t>, long long> tree;
    std::unordered_map<std::pair<size_t, size_t>, long long, PairHasher> ht;

    int c;
    std::size_t i, j;
    long long val;

    std::size_t n, m;
    std::cin >> c;
    std::cin >> m >> n;
    int t = c;
    while (t--) {
        std::cin >> i >> j >> val;
        arr.push_back(std::make_tuple(i, j, val));
        tree[std::make_pair(i, j)] = val;
        ht[std::make_pair(i, j)] = val;
    }
    SparseMatrix sm(m, n, arr);
    
{
    auto start = std::chrono::steady_clock::now();
    long long temp = 0;
    for (auto [i, j, val] : arr) {
        //std::make_pair(i, j);
        temp ^= sm(i, j);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = (end - start) * 1000;
    std::cout << duration.count() << std::endl;
    std::cout << "XORED: " << temp << '\n';
    auto res = sm.EqualityCount();
    for (auto&& el : res) {
        std::cout << el << std::endl;
    }
}
{
    auto start = std::chrono::steady_clock::now();
    long long temp = 0;
    for (auto [i, j, val] : arr) {
        temp ^= tree[std::make_pair(i, j)];
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = (end - start) * 1000;
    std::cout << duration.count() << std::endl;
    std::cout << "XORED: " << temp << '\n';
}
{
    auto start = std::chrono::steady_clock::now();
    long long temp = 0;
    for (auto [i, j, val] : arr) {
        temp ^= ht[std::make_pair(i, j)];
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = (end - start) * 1000;
    std::cout << duration.count() << std::endl;
    std::cout << "XORED: " << temp << '\n';
}
/*
    //std::cout << sm;
    auto it_mid = sm.begin();
    std::cout << std::get<0>(*it_mid) << ' ' << std::get<1>(*it_mid) << std::endl;
    it_mid += (sm.end() - sm.begin()) / 2;
    std::cout << std::get<0>(*it_mid) << ' ' << std::get<1>(*it_mid) << std::endl;
    std::cout << "Density is: " <<  sm.Density() << std::endl;
*/
    return 0;
}
