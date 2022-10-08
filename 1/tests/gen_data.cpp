#include <iostream>
#include <cstdlib>
#include <map>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }
    std::size_t count = atoll(argv[1]);
    std::size_t m = atoll(argv[2]);
    std::size_t n = atoll(argv[3]);

    std::cout << count << '\n';
    std::cout << m << ' ' << n << '\n';

    FILE *fd = fopen("/dev/urandom", "rb");
    if (!fd) {
        return 1;
    }
    std::size_t total = 3 * count;
    auto values = new std::size_t[total];
    std::size_t written = 0;
    while (written < total) {
        values += written;
        written = fread(values, sizeof(std::size_t), total - written, fd);
    }
    fclose(fd);

    std::map<std::pair<std::size_t, std::size_t>, long long> tree;
    std::size_t i, j, value;
    for (auto it = 0; it < total; it += 3) {
        i = values[it] % m;
        j = values[it + 1] % n;
        value = values[it + 2];
        tree[std::make_pair(i, j)] = value;
    }
    delete[] values;
    for (auto&& [coords, value] : tree) {
        std::cout << coords.first << ' ' << coords.second << ' ' << value << '\n';
    }
    
    return 0;
}