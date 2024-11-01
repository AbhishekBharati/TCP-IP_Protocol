#include "../../include/network/socket.h"
#include "../../config/config.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

Socket::Socket() : sock_fd(-1) {}

Socket::~Socket() {
  close();
}

bool Socket::create() {
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_fd < 0){
    std::cerr << "Socket Creation Failed." << std::endl;
    return false;
  }
  return true;
}

bool Socket::bind(int port) {
  if(!isValid()) return false;

  sockaddr_in address;
  std::memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if(::bind(sock_fd, (struct sockaddr*) &address, sizeof(address)) < 0){
    std::cerr<< " Socket binding failed." << std::endl;
    return false;
  }
  return true;
}

bool Socket::listen(int backlog) {
  if(!isValid()) return false;

  if(::listen(sock_fd, backlog) < 0){
    std::cerr << "Socket Listen Failed." << std::endl;
    return false;
  }
  return true;
}

Socket* Socket::accept() const {
  if(!isValid()) return nullptr;
  int new_sock_fd = ::accept(sock_fd, nullptr, nullptr);
  if(new_sock_fd < 0){
    std::cerr << "Socket accept failed." << std::endl;
    return nullptr;
  }

  // Return a new Socket object for the accepted connection.
  Socket *new_socket = new Socket();
  new_socket->sock_fd = new_sock_fd;
  return new_socket;
}

bool Socket::connect(const std::string &host, int port){
  if(!isValid()) return false;

  sockaddr_in address;
  std::memset(&address,0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);

  // Convert hostname to binary I.P.
  if(inet_pton(AF_INET, host.c_str(), &address.sin_addr) <= 0){
    std::cerr << "Invalid address or address not supported." << std::endl;
    return false;
  }

  if(::connect(sock_fd, (struct sockaddr*) &address, sizeof(address)) < 0){
    std::cerr << "Socket Connection failed." << std::endl;
    return false;
  }

  return true;
}

bool Socket::send(const std::string &message) const {
  if(!isValid()) return false;

  int sent_bytes = ::send(sock_fd, message.c_str(), message.size(), 0);
  if(sent_bytes < 0){
    std::cerr << "Socket send failed. " << std::endl;
    return false;
  }
  return true;
}

int Socket::receive(std::string &message) const {
  if(!isValid()) return -1;

  char buffer[Config::buffer_size];
  int received_bytes = ::recv(sock_fd, buffer, Config::buffer_size, 0);
  if(received_bytes > 0){
    message.assign(buffer, received_bytes);
  } else if(received_bytes < 0) {
    std::cerr << "Socket receive failed." << std::endl;
  }

  return received_bytes;
}

bool Socket::close() {
  if(isValid()) {
    ::close(sock_fd);
    sock_fd = -1;
  }
  return true;
}

bool Socket::isValid() const {
  return sock_fd >= 0;
}
