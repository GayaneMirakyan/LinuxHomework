#include "ParallelMatrix.h"
#include <iostream>
#include <chrono>

using namespace std::chrono;

int main()
{
    // creating class type object
    ParallelMatrix m(10, 10);
    
    // running Sum() and counting time 
    auto start = high_resolution_clock::now();
    m.Sum();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    std::cout << "Time for Sum(): " << duration.count() << " nanoseconds" << std::endl;

    // running SumParellel(4) and counting time for 4 threads
    start = high_resolution_clock::now();
    m.SumParallel(4);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    std::cout << "Time for SumParallel(4): " << duration.count() << " nanoseconds" << std::endl;

    // running SumParellel(8) and counting time for 8 threads
    start = high_resolution_clock::now();
    m.SumParallel(8);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    std::cout << "Time for SumParallel(8): " << duration.count() << " nanoseconds" << std::endl;
    
    // running SumParellel(16) and counting time for 16 threads
    start = high_resolution_clock::now();
    m.SumParallel(16);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    std::cout << "Time for SumParallel(16): " << duration.count() << " nanoseconds" << std::endl;

    // running SumParellel(100) and counting time for 100 threads
    start = high_resolution_clock::now();
    m.SumParallel(100);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    std::cout << "Time for SumParallel(100): " << duration.count() << " nanoseconds" << std::endl;
}