#ifndef PARALLELMATRIX
#define PARALLELMATRIX

class ParallelMatrix
{
private:
    const int n = 10;
    const int m = 10;
    int matrix[400][10] = {};
    friend void* sum_for_parallel(void* arg);
public:
    ParallelMatrix(int _n, int _m);
    void initMatrix();
    void Sum();
    void SumParallel(int thread_count);
    void makeingarray(int* arr);
};
// struct for makeing array from matrix
struct arrayFromMat
{
	int* arr;
	int start_index;
	int count;
};

#endif