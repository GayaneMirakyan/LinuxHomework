#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <cstdlib>

int main() {

    
    while(true)
    {
	char* argv;
        char* arguments[100];
        char str[10000];

	std::cout << "GayaneShell: ";
	// get an arguments
	std::cin.getline(str, 100);

	// split string by space
	argv = strtok (str, " ");
 
	int i = 0;
        while(argv != NULL)
	{
	    arguments[i] = argv;
	    i++;
	    arguments[i] = 0;
	    argv = strtok(NULL, " ");
	}

        // create new process
        pid_t pid = fork();
        
	// error
        if(pid < 0)
        {
            std::cout << "Something went wrong " << std::endl;
            return errno;
        }
        
	// child process
        if(pid == 0)
	{
            // get child pid
            pid_t childPid = getpid();
            // make silentshell folder, and childPid subfolder
            int maked = mkdir(((std::string)"/opt/silentshell/" + std::to_string(childPid)).c_str(), 0777);
             if(maked < 0){
                std::cout << "Error while creating the folder" << std::endl;
                exit(errno);
            }

 	    // execute a file
            execvp(arguments[0], arguments);
            std::cout << "This is a child process" << std::endl;
	    exit(0);
        }

	// parent process
	if(pid > 0)
        {
             wait(NULL);
        }
    }

    return 0;
}
