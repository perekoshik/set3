#include <bits/stdc++.h>
#include "ArrayGenerator.h"
#include "SortTester.h"
#include <filesystem>

void mergeSort(std::vector<int>& a) {
    std::vector<int> temp(a.size());
    std::function<void(int,int)> sort = [&](int l, int r) {
        if (r - l <= 1) return;
        int m = (l + r) / 2;
        sort(l, m);
        sort(m, r);
        int i = l, j = m, k = l;
        while (i < m && j < r) temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
        while (i < m) temp[k++] = a[i++];
        while (j < r) temp[k++] = a[j++];
        for (int t = l; t < r; ++t) a[t] = temp[t];
    };
    sort(0, a.size());
}

void insertionSortRange(std::vector<int>& a, int l, int r) {
    for (int i = l + 1; i < r; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= l && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

void hybridMergeSort(std::vector<int>& a, int threshold) {
    std::vector<int> temp(a.size());
    std::function<void(int,int)> sort = [&](int l, int r) {
        int len = r - l;
        if (len <= 1) return;
        if (len <= threshold) {
            insertionSortRange(a, l, r);
            return;
        }
        int m = (l + r) / 2;
        sort(l, m);
        sort(m, r);
        int i = l, j = m, k = l;
        while (i < m && j < r) temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
        while (i < m) temp[k++] = a[i++];
        while (j < r) temp[k++] = a[j++];
        for (int t = l; t < r; ++t) a[t] = temp[t];
    };
    sort(0, a.size());
}

int main(int argc, char** argv) {
    const int minSize = 500;
    const int maxSize = 10000;
    const int step = 100;
    std::vector<int> sizes;
    for (int n = minSize; n <= maxSize; n += step) sizes.push_back(n);

    ArrayGenerator generator(maxSize, 0, 6000, 20240601);
    std::vector<std::vector<int>> randomData;
    std::vector<std::vector<int>> reversedData;
    std::vector<std::vector<int>> almostData;
    randomData.reserve(sizes.size());
    reversedData.reserve(sizes.size());
    almostData.reserve(sizes.size());

    for (int n : sizes) {
        randomData.push_back(generator.randomArray(n));
        reversedData.push_back(generator.reversedArray(n));
        almostData.push_back(generator.almostSortedArray(n));
    }

    SortTester tester(5);

    std::string baseDir = (argc > 1) ? argv[1] : "task1";
    std::filesystem::create_directories(baseDir);

    auto outPath = [&](const std::string& name) {
        return baseDir + '/' + name;
    };

    tester.benchmark(sizes, mergeSort, randomData, outPath("random_merge.csv"));
    tester.benchmark(sizes, mergeSort, reversedData, outPath("reversed_merge.csv"));
    tester.benchmark(sizes, mergeSort, almostData, outPath("almost_merge.csv"));

    std::vector<int> thresholds = {5, 10, 20, 30, 50};
    for (int threshold : thresholds) {
        auto hybrid = [threshold](std::vector<int>& arr) {
            hybridMergeSort(arr, threshold);
        };
        tester.benchmark(sizes, hybrid, randomData, outPath("random_hybrid_" + std::to_string(threshold) + ".csv"));
        tester.benchmark(sizes, hybrid, reversedData, outPath("reversed_hybrid_" + std::to_string(threshold) + ".csv"));
        tester.benchmark(sizes, hybrid, almostData, outPath("almost_hybrid_" + std::to_string(threshold) + ".csv"));
    }

    return 0;
}
