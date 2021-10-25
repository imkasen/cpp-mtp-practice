#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

const int ITERATIONS = 10;

void print_results(const std::vector<double> &times) {
    std::cout << std::fixed;
    std::cout << "#\tTime (s)" << std::endl;

    for (int i = 0; i < ITERATIONS; ++i) {
        std::cout << i << "\t" << times[i] / 1e6 << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Avg. time: "
        << std::accumulate(times.cbegin(), times.cend(), 0.0) / static_cast<double>(times.size()) / 1e6 << " (s)"
        << std::endl;

    std::cout << "Min. time: "
        << *std::min_element(times.cbegin(), times.cend()) / 1e6 << " (s)"
        << std::endl;

    std::cout << "Max. time: "
        << *std::max_element(times.cbegin(), times.cend()) / 1e6 << " (s)"
        << std::endl;
}

