#pragma once
#include <vector>
#include <chrono>
#include <functional>
#include <numeric>
#include <fstream>

class SortTester {
public:
    using SortFunc = std::function<void(std::vector<int>&)>;

    SortTester(int repetitions = 5)
        : repetitions_(repetitions) {}

    double measure(SortFunc sorter, std::vector<int> data) {
        long long total = 0;
        for (int i = 0; i < repetitions_; ++i) {
            auto copy = data;
            auto start = std::chrono::high_resolution_clock::now();
            sorter(copy);
            auto end = std::chrono::high_resolution_clock::now();
            total += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        return static_cast<double>(total) / repetitions_;
    }

    void benchmark(const std::vector<int>& sizes,
                   SortFunc sorter,
                   const std::vector<std::vector<int>>& datasets,
                   const std::string& filename) {
        std::ofstream out(filename);
        out << "size,time_microseconds\n";
        for (size_t i = 0; i < sizes.size(); ++i) {
            double t = measure(sorter, datasets[i]);
            out << sizes[i] << ',' << t << '\n';
        }
    }

private:
    int repetitions_;
};
