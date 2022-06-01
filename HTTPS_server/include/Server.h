#ifndef HTTPS_SERVER
#define HTTPS_SERVER

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
#include <stdexcept>
#include <list>
#include "json.hpp"


namespace https{
class Response {

};

class requestHendler {
  virtual Response handler() = 0;
};

class staticVebsite : public requestHendler {
  virtual Response handler() override {

  }
};

class methodPath : public requestHendler {
  virtual Response handler() override {

  }
};

class path : public requestHendler {
  virtual Response handler() override {

  }
};

class HTTPS {
private:
  std::list<requestHendler *> hendlers;
  sockaddr_in address;
  int port;
  int socketFD;
public:
  HTTPS(int port_m) : port(port_m) {

    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    // validate socket descriptor
    if (socketFD < 0) {
      std::string message = strerror(errno);
      throw std::invalid_argument("Error while creating a socket: " + message);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
  }
  ~HTTPS() = default;

  [[noreturn]] void run();
  void getRequest();
  void sendReponse();
  void bindSocket();
  void listenClients();

};
}


#endif