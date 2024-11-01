#ifndef SOCKET_H
#define SOCKET_H
#include <string>

class Socket {
  public : 
    Socket();
    ~Socket();

    bool create();
    bool bind(int port);
    bool listen(int backlog = 5);
    Socket *accept() const;
    bool connect(const std::string &host, int port);
    bool send(const std::string &message) const;
    int receive(std::string &message) const;
    bool close();

    bool isValid() const;

  private :
    int sock_fd; // Socket File Descriptor.
};

#endif // SOCKET_H
