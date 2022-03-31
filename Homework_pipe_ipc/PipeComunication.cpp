#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <random>
#include <sys/wait.h>
#include <cerrno>

enum pipeReadWrite {
  READ,
  WRITE,
  COUNT
};

int main() {
  long long sumInParent = 0; 
  long long sum = 0;
  int number, ParallelWorkers;
  int* array = new int[number];
  int pipeForParentAndChild[COUNT];

  std::cin >> number >> ParallelWorkers;

  // makeing array with random numbers
  for(size_t i = 0; i < number; i++) {
    srand ( time(NULL) );
    array[i] = rand() % 10;
    sumInParent += array[i];
  }

  // create pipe and cheak if it is created
  if (pipe(pipeForParentAndChild) < 0) {
    std::cout << "Unable to create pipe";
    return errno;
  }

  for(int i = 0; i < ParallelWorkers; i++) {

    pid_t pid = fork();
    if(pid < 0) {
      std::cout << "ERROR while creating child process";
      return errno;
    }

    // child process
    if(pid > 0){
      close(pipeForParentAndChild[READ]);
      long long childSum = 0;
      int start = i * number / ParallelWorkers;
      int end = start + number / ParallelWorkers;
      for(int j = start; j < end; j++) {
        childSum += array[j];
      }

      if (i == ParallelWorkers - 1) {
          childSum += array[end];
      }

      if(write(pipeForParentAndChild[WRITE], &childSum, sizeof(childSum)) < 0) {
        std::cout << "ERROR while writing";
        return errno;
      }

      // close fd after using
      close(pipeForParentAndChild[WRITE]);
      exit(0);
    }
  }

  for (int i = 0; i < ParallelWorkers; i++) {
      long long curSum = 0;
      if(read(pipeForParentAndChild[READ], &curSum, sizeof(curSum)) < 0) {
        std::cout << "ERROR while reading";
        return errno;
      }
      sum += curSum;
  }

  // waiting processes
  wait(NULL);
  std::cout << std::endl << "main process sum: " << sumInParent << std::endl;
  std::cout << "sum in child processes " <<  sum << std::endl;

  // close fd after using
  close(pipeForParentAndChild[READ]);

  return 0;
}