#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>

int main(int argc, char **argv) {

  if (argc < 3) {
    std::cerr << "Too few arguments" << std::endl;
    exit(1);
  }

  char *hostStr = argv[1];
  int port = atoi(argv[2]);

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(hostStr);

  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  int connected = connect(serverSocket, (const sockaddr *) &address, sizeof(address));
  if (connected < 0) {
    std::cerr << "Could not connect to a remote host " << std::endl;
    exit(errno);
  }

  std::string data;
  std::cout << "Connected. Please enter a number" << std::endl;

  std::cin >> data;
  ssize_t sentBytes = send(serverSocket, data.data(), data.size(), 0);

  if (sentBytes < 0) {
    std::cerr << "Could not send bytes to the server: Error " << strerror(errno) << std::endl;
    exit(errno);
  }

  // finish transmiting data to server
  shutdown(serverSocket, 1);

  const int BUFFER_SIZE = (1 << 10);
  char buffer[BUFFER_SIZE];
  ssize_t offset = 0;
  ssize_t readBytes;
  while ((readBytes = recv(serverSocket, buffer + offset, 8, 0)) > 0) {
    offset += readBytes;
  }
  if (readBytes < 0) {
    std::cerr << "Error while reading" << strerror(errno) << std::endl;
  }
  buffer[offset] = '\0';

  std::cout << "Got result from server: " << buffer << std::endl;

  close(serverSocket);

  return 0;
}
