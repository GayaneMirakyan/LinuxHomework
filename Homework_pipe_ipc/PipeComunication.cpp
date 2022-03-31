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

enum dist {
  BEGIN,
  FINISH,
  DIST_COUNT
};

int main() {
  size_t sumInParent = 0, sum = 0;
  int number, ParallelWorkers;
  int readmessageChild[DIST_COUNT] = {}, writemessageParent[DIST_COUNT] = {}, writemessageChilde, readmessageParent;
  int* array = new int[number];
  int pipeParentToChild[COUNT], pipeChildToParent[COUNT];

  std::cin >> number >> ParallelWorkers;

  // makeing array with random numbers
  for(size_t i = 0; i < number; i++) {
    array[i] = rand() % 10;
    sumInParent += array[i];
  }

  // create pipe and cheak if it is created
  if (pipe(pipeChildToParent) < 0) {
    std::cout << "Unable to create pipe";
    return errno;
  }

  for(int i = 0; i < ParallelWorkers; i++) {
    // create pipe and cheak if it is created
    if (pipe(pipeParentToChild) < 0) {
      std::cout << "Unable to create pipe";
      return errno;
    }

    // creating processes
    pid_t pid = fork();

    // cheaking if process is created
    if(pid < 0) {
      std::cout << "ERROR while creating child process";
      return errno;
    }

    // parent process
    if(pid == 0) {
      writemessageParent[BEGIN] = writemessageParent[FINISH];
      if(i + (number/ParallelWorkers) >= number || i+1 == ParallelWorkers) {
        writemessageParent[FINISH] = number;
      }
      else {
        writemessageParent[FINISH] =  writemessageParent[BEGIN] + number/ParallelWorkers;
      }

      // writing and cheaking
      if(write(pipeParentToChild[WRITE], writemessageParent, sizeof(writemessageParent)) < 0){
        std::cout << "ERROR while writing";
        return errno;
      }
      // reading and cheaking
      if(read(pipeChildToParent[READ], &readmessageParent, sizeof(readmessageParent)) < 0) {
        std::cout << "ERROR while reading";
        return errno;
      }
      sum += readmessageParent;
    }

    // child process
    if(pid > 0){
      // close unused fd
      close(pipeChildToParent[READ]);
      close(pipeParentToChild[WRITE]);

      if(read(pipeParentToChild[READ], readmessageChild, sizeof(readmessageChild)) < 0) {
        std::cout << "ERROR while reading";
        return errno;
      }
      writemessageChilde = 0;
      for(int j = readmessageChild[BEGIN]; j < readmessageChild[FINISH]; j++) {
        writemessageChilde += array[j];
      }

      if(write(pipeChildToParent[WRITE], &writemessageChilde, sizeof(writemessageChilde)) < 0) {
        std::cout << "ERROR while writing";
        return errno;
      }

      // close fd after using
      close(pipeChildToParent[WRITE]);
      close(pipeParentToChild[READ]);
      exit(0);
    }
  }

  // waiting processes
  wait(NULL);
  std::cout << std::endl << "natural sum: " << sumInParent << std::endl;
  std::cout << "sum in child processes " <<  sum << std::endl;

  // close fd after using
  close(pipeParentToChild[WRITE]);
  close(pipeChildToParent[READ]);

  return 0;
}
