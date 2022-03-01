#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <cstring>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <pwd.h>

// function for signal handeling and changeing signal action
void signal_handler(int signal_num, siginfo_t* siginfo, void* ucontext ) {
    if(signal_num != SIGUSR1) {
        return;
    }
    // cast void* to ucontext_t*
    struct ucontext_t* context = (ucontext_t*)ucontext;

    pid_t pid = siginfo->si_pid;
    uid_t uid = siginfo->si_uid;

    // print PID and UID
    std::cout << "signal is " << signal_num << std::endl 
                << " - The PID of the sender " << pid << std::endl 
                << " - The UID of the sender " << uid << std::endl;

    // print user name
    struct passwd *pw;
    pw = getpwuid(uid);
    std::cout << " - The user name of the sender " << pw->pw_name << std::endl;

    // print registers
    std::cout << " - REG_RIP =  " <<  context->uc_mcontext.gregs[REG_RIP]<< std::endl;
    std::cout << " - REG_RAX =  " <<  context->uc_mcontext.gregs[REG_RAX]<< std::endl;
    std::cout << " - REG_RBX =  " <<  context->uc_mcontext.gregs[REG_RBX]<< std::endl;

    exit(0);
}

int main() {
    // definition
    struct sigaction action;

    // initilize struct action with 0
    memset(&action, 0, sizeof(struct sigaction));

    // I will write signal handler like this (*sa_sigaction)(int, siginfo_t *, void *)
    action.sa_sigaction = signal_handler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &action, NULL);

    // infinite loop
    while(true) {
        std::cout << "Infinite" << std::endl;
        sleep(1);
        kill(getpid(), 10);
    }
    return 0;
}