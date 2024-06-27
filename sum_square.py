#include <iostream>
#include <vector>
#include <thread>
#include <numeric>

// 函数：计算从start到end的所有整数的平方和
void partial_sum_squares(int start, int end, long long& result) {
    result = 0;
    for (int i = start; i <= end; ++i) {
        result += static_cast<long long>(i) * i;
    }
}

// 主函数
int main() {
    const int N = 1000000; // 要计算平方和的最大整数
    const int num_threads = std::thread::hardware_concurrency(); // 获取硬件支持的最大线程数
    std::vector<std::thread> threads;
    std::vector<long long> results(num_threads, 0);

    int block_size = N / num_threads;

    // 创建并启动线程
    for (int i = 0; i < num_threads; ++i) {
        int start = i * block_size + 1;
        int end = (i == num_threads - 1) ? N : (i + 1) * block_size;
        threads.emplace_back(partial_sum_squares, start, end, std::ref(results[i]));
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 汇总结果
    long long total_sum = std::accumulate(results.begin(), results.end(), 0LL);

    std::cout << "Sum of squares from 1 to " << N << " is " << total_sum << std::endl;

    return 0;
}
