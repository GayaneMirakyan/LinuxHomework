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

void parse() {

}

void HTTPS::bindSocket() {
  if (bind(socketFD, (const struct sockaddr *) &address, sizeof(address)) < 0) {
    std::string message = strerror(errno);
    throw std::invalid_argument("Could not bind to given port: " + message);
  }
}

void HTTPS::listenClients() {
  if (listen(socketFD, 1024) < 0) {
    std::string message = strerror(errno);
    throw std::invalid_argument("Could not bind to given port: " + message);
  }
}

void g(int x, int y) {

}

struct F {
  void operator()(int x, int y) {

  }
};

[[noreturn]] void HTTPS::run() {
  bindSocket();
  listenClients();
  std::cout << "Server listens on " << port << std::endl;
  while (true) {
    sockaddr_in clientAddress{};
    unsigned int clientAddressLength = sizeof(clientAddress);
    std::cout << "Waiting new client..." << std::endl;
    int clientFd = accept(socketFD, (struct sockaddr *) &clientAddress, &clientAddressLength);
    if (clientFd < 0) {
      std::cerr << "Error while accepting connection request" << strerror(errno) << std::endl;
      // retry connect to clients
      continue;
    }
    std::cout << "New client connected" << std::endl;

    const int BUFFER_SIZE = (1 << 10);
    char buffer[BUFFER_SIZE];
    ssize_t offset = 0;
    ssize_t readBytes = 0;
    while ((readBytes = recv(clientFd, buffer + offset, 8, 0)) > 0) {
      offset += readBytes;
    }
    if (readBytes < 0) {
      std::cerr << "Error while reading" << strerror(errno) << std::endl;
    }
    buffer[offset] = '\0';
    int number = std::stoi(buffer);
    std::cout << "Received from client " << number << std::endl;

    struct in_addr clientAddr = clientAddress.sin_addr;
    int clientPort = ntohs(clientAddress.sin_port);
    char *clientIp = inet_ntoa(clientAddr);

    //

    close(clientFd);
  }

}

int main() {

  HTTPS server(9090);
  server.run();
  return 0;
}