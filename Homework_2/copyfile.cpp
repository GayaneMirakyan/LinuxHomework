#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>
#include <sys/types.h>

#define BUFFERSIZE 16

int main(int argc, char** argv) {

        if(argc < 3){
                std::cout << "No file to read" << std::endl;
                exit(1);
        }

        //get source file path
        const char* sourcefile = argv[1];

        //open file for read only
        int fd1 = open(sourcefile, O_RDONLY);

        //get destination file path
        const char* destinationfile = argv[2];

        //open destination file
        int fd2 = open(destinationfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);

        //check if file was not opened
        if(fd1 < 0) {
                std::cout << "Could not open file" << std::endl;
		exit(errno);
        }
	//allocate a buffer to read from file
	char* buffer = new char[BUFFERSIZE + 1];
	
	//geting logical size of source file
	off_t logicalsize = lseek(fd1, 0, SEEK_END);

	//printing logical size of sorce file
	std::cout << "Logical size of source file is " << logicalsize << std::endl;

	//changeing cursore 
	lseek(fd1, 0, SEEK_SET);

	while(true) {
		//read data_file bytes from file to buffer
                int readdatabytes = read(fd1, buffer, BUFFERSIZE);

                //check if could not read
                if(readdatabytes < 0) {
                	std::cout << "Could not read from file" << std::endl;
                	exit(errno);
                }
		//check if there is nothing to read
                if(readdatabytes == 0) {
                	break;
                }

               //write content of buffer into destination file
               int writtendata = write(fd2, buffer, readdatabytes);

               //check if could not write
               if(writtendata < 0){
		       std::cout << "Could not write" << std::endl;
                       exit(errno);
                }

	}


	delete[] buffer;
	int closed1 = close(fd1);
        int closed2 = close(fd2);
        return 0;
}


