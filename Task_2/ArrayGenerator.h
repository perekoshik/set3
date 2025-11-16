#pragma once
#include <vector>
#include <random>
#include <algorithm>

class ArrayGenerator {
public:
    ArrayGenerator(int maxSize, int minValue, int maxValue, int seed = 123456789)
        : maxSize_(maxSize), minValue_(minValue), maxValue_(maxValue), rng_(seed), dist_(minValue, maxValue) {
        generateBaseData();
    }

    std::vector<int> randomArray(int n) {
        std::vector<int> result(baseRandom_.begin(), baseRandom_.begin() + n);
        std::shuffle(result.begin(), result.end(), rng_);
        return result;
    }

    std::vector<int> reversedArray(int n) {
        return std::vector<int>(baseReversed_.begin(), baseReversed_.begin() + n);
    }

    std::vector<int> almostSortedArray(int n, double fraction = 0.01) {
        std::vector<int> arr(baseSorted_.begin(), baseSorted_.begin() + n);
        int swaps = static_cast<int>(n * fraction);
        std::uniform_int_distribution<int> idxDist(0, n - 1);
        for (int i = 0; i < swaps; ++i) {
            int a = idxDist(rng_);
            int b = idxDist(rng_);
            std::swap(arr[a], arr[b]);
        }
        return arr;
    }

private:
    int maxSize_;
    int minValue_;
    int maxValue_;
    std::mt19937 rng_;
    std::uniform_int_distribution<int> dist_;
    std::vector<int> baseRandom_;
    std::vector<int> baseSorted_;
    std::vector<int> baseReversed_;

    void generateBaseData() {
        baseRandom_.resize(maxSize_);
        for (int i = 0; i < maxSize_; ++i) {
            baseRandom_[i] = dist_(rng_);
        }
        baseSorted_ = baseRandom_;
        std::sort(baseSorted_.begin(), baseSorted_.end());
        baseReversed_ = baseSorted_;
        std::reverse(baseReversed_.begin(), baseReversed_.end());
    }
};
