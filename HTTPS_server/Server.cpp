#include "include/Server.h"

namespace https{
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

}


int main() {

  https::HTTPS server(9090);
  server.run();
  return 0;
}