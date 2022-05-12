#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <list>

class Response {

};

class requestHendler {
  virtual Response hendler() = 0;
};

class staticVebsite : public requestHendler {
  virtual Response hendler () override {

  }
};

class methodPath : public  requestHendler {
  virtual Response hendler () override {

  }
};

class path : public requestHendler {
  virtual Response hendler () override {

  }
};

class HTTPS {
private:
  std::list<requestHendler*> hendlers;
  sockaddr_in address;
  int Port;
  int SocketFD;


public:
  HTTPS(int port_m, sockaddr_in address_m) : Port(port_m), address(address_m) {

    SocketFD = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(Port);
    address.sin_addr.s_addr = htonl (INADDR_ANY);
  }
  ~HTTPS();

  void run();
  void getRequest();
  void sendReponse();
  void checkSocket();
  void checkBound();
  void checkListen();


};

void HTTPS::checkSocket() {
  if(SocketFD < 0){
    std::cerr << "Error while creating a socket" << std::endl;
    HTTPS::~HTTPS();
    exit(errno);
  }
}

void HTTPS::checkBound() {
  int bound = bind(SocketFD, (const struct sockaddr*) &address, sizeof(address));

  if(bound < 0){
    std::cerr << "Could not bind to given port" << std::endl;
    HTTPS::~HTTPS();
    exit(errno);
  }
}

void HTTPS::checkListen() {
  int listening = listen(SocketFD, 1024);

  if(listening < 0){
    std::cerr << "Could not start listening" << std::endl;
    HTTPS::~HTTPS();
    exit(errno);
  }
}

void HTTPS::run() {

  checkSocket();
  checkBound();
  checkListen();
  
  while(true){
    sockaddr_in clientAddress;
    unsigned int clientAddressLength;
    int clientFd = accept(SocketFD,(struct sockaddr*)  &clientAddress, &clientAddressLength);
    struct in_addr clientAddr = clientAddress.sin_addr;
    int clientPort = ntohs(clientAddress.sin_port);
    char* clientIp = inet_ntoa(clientAddr);

    //

    close(clientFd);
  }

}


int main () {

  return 0;
}