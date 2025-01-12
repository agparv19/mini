#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include <mutex>

// g++ myatomic.cpp -o myatomic
// ./myatomic


// Structure without padding (prone to false sharing)
struct WithoutPadding {
    std::atomic<int64_t> var1;
    std::atomic<int64_t> var2;
};

// Structure with padding to avoid false sharing (aligns to 64-byte cache line)
struct WithPadding {
    std::atomic<int64_t> var1;
    alignas(64) std::atomic<int64_t> var2;  // Align var2 to avoid sharing the same cache line
};

// Structure with std::mutex (locks to avoid race conditions)
struct WithMutex {
    int64_t var1 = 0;
    int64_t var2 = 0;
    std::mutex mtx;
};

// Number of iterations per thread
constexpr int NUM_ITERATIONS = 1000000;

// Number of threads
constexpr int NUM_THREADS = 8;

// Function to update variables in parallel without padding (potential false sharing)
void updateWithoutPadding(WithoutPadding& data) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        data.var1++;
        data.var2++;
    }
}

// Function to update variables in parallel with padding (no false sharing)
void updateWithPadding(WithPadding& data) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        data.var1++;
        data.var2++;
    }
}

// Function to update variables using std::mutex to avoid race conditions
void updateWithMutex(WithMutex& data) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::lock_guard<std::mutex> lock(data.mtx);  // Lock the mutex for each update
        data.var1++;
        data.var2++;
    }
}

// Function to measure execution time of a given operation
template <typename Func, typename Data>
long long measurePerformance(Func updateFunc, Data& data) {
    auto start = std::chrono::high_resolution_clock::now();

    // Create and launch threads
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(updateFunc, std::ref(data));
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    // Data structures
    WithoutPadding dataWithoutPadding = {0, 0};
    WithPadding dataWithPadding = {0, 0};
    WithMutex dataWithMutex;

    // Measure performance with mutex
    long long timeWithMutex = measurePerformance(updateWithMutex, dataWithMutex);
    std::cout << "Execution time with std::mutex: " << timeWithMutex << " ms\n";

    // Measure performance without padding
    long long timeWithoutPadding = measurePerformance(updateWithoutPadding, dataWithoutPadding);
    std::cout << "Execution time (atmoic) without padding: " << timeWithoutPadding << " ms\n";

    // Measure performance with padding
    long long timeWithPadding = measurePerformance(updateWithPadding, dataWithPadding);
    std::cout << "Execution time (atomic) with padding: " << timeWithPadding << " ms\n";

    return 0;
}
