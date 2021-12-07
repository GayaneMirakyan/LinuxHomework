#include "ParallelMatrix.h"
#include <ctime>
#include <iostream>
#include <pthread.h>

//  init method that initializes all the cells with random integers
void ParallelMatrix::initMatrix() 
{
     for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            time_t num = time(nullptr);
            time_t temp = time(nullptr);
            matrix[i][j] = num%(j+1+temp%(i+1));
        }
    }
}

// constructor
ParallelMatrix::ParallelMatrix(int _n, int _m) : n(_n), m(_m) {
    initMatrix();
}

// Sum method that count sum of all cells
void ParallelMatrix::Sum() 
{
    long long int sum = 0;
    for(int i = 0; i < n; i++) 
    {
        for(int j = 0; j < m; j++) 
        {
            sum += matrix[i][j];
        }
    }
    return;
}
// function which I will give as an argument while makeing thread
void* sum_for_parallel(void* arg)
{
    arrayFromMat* args = (arrayFromMat*) arg;
	int curr_sum = 0;
	for(int i = args->start_index; i < args->start_index + args->count; i++)
	{
		curr_sum += args->arr[i];
	}
	return (void*) (new int(curr_sum));
}
// function for makeing array from matrix
void ParallelMatrix::makeingarray(int* matrix_array)
{
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            matrix_array[k] = matrix[i][j];
            k++;
        }
    }
    return;
}
// for creating threads, and counting sum of cells in threads
void ParallelMatrix::SumParallel(int thread_count)
{
    int matrix_array[4000] = {};
    makeingarray(matrix_array);

    pthread_t* threads = new pthread_t[thread_count];
    arrayFromMat* arr = new arrayFromMat[thread_count];

    for(int i = 0; i < thread_count; i++) 
    {
        arr[i].arr = matrix_array;
        arr[i].start_index = i * n * m / thread_count; 
        arr[i].count = n * m / thread_count;
    }

    for(int i = 0; i < thread_count; i++) 
    {
        int new_thread = pthread_create(&threads[i], NULL, sum_for_parallel, &arr[i]);
        if(new_thread != 0)
        {
            std::cout << "Error while createing" << std::endl;
            exit(new_thread);
        }
    }
    int sum = 0;
    void* curr_sum;
	for(int i = 0; i < thread_count; ++i)
	{
		int joined = pthread_join(threads[i], &curr_sum);
		if (joined != 0)
		{
            std::cout << "Error while joining" << std::endl;
			exit(joined);
		}
		int* curr_sum_int = (int*) curr_sum;
		sum += *curr_sum_int;
		delete curr_sum_int;
	}
}