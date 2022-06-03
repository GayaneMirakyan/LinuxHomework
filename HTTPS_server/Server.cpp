#include "include/Server.h"

using namespace nlohmann;
namespace https{

void HTTPS::bindSocket() {
  if (bind(socketFD, (const struct sockaddr *) &address, sizeof(address)) < 0) {
    std::string message = strerror(errno);
    throw std::invalid_argument("Could not bind to given port: " + message);
  }
}

void HTTPS::listenClients() const {
  if (listen(socketFD, 1024) < 0) {
    std::string message = strerror(errno);
    throw std::invalid_argument("Could not bind to given port: " + message);
  }
}

nlohmann::json HTTPS::getRequest(int clientFd) {
  const int BUFFER_SIZE = (1 << 10);
  char buffer[BUFFER_SIZE];
  ssize_t offset = 0;
  ssize_t readBytes;
  while ((readBytes = recv(clientFd, buffer + offset, 8, 0)) > 0) {
    offset += readBytes;
  }
  if (readBytes < 0) {
    std::cerr << "Error while reading" << strerror(errno) << std::endl;
  }
  buffer[offset] = '\0';
  // parse json
  return json::parse(buffer);
}

void HTTPS::sendResponse(const nlohmann::json& response, int clientFd) {
  std::string data = response.dump();
  ssize_t sentBytes = send(clientFd, data.data(), data.size(), 0);

  if (sentBytes != data.size()) {
    std::string message = strerror(errno);
    throw std::invalid_argument("Could not send response to the client: Error " + message);
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
    nlohmann::json request = getRequest(clientFd);
    std::cout << "Recieved client request " << request.dump(4) << std::endl;
    nlohmann::json response = onGetRequest(request);
    // send client response
    sendResponse(response, clientFd);
    // finish transmiting data to client
    shutdown(clientFd, 1);

    close(clientFd);
  }

}

} // namespace https

// usage
class MyServer : public https::HTTPS {
public:
  // inherit parent constructor
  using https::HTTPS::HTTPS;
  nlohmann::json onGetRequest(nlohmann::json request) override {
    return request;
  }
};


int main() {
  MyServer server(9090);
  server.run();
}