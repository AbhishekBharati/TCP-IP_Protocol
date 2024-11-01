#include <iostream>
#include "../config/config.h"
#include "../include/network/socket.h"

int main(){
  // Load configuration from file (if available)
  Config::load("../config/config.json");

  // Access config values and print them to check :-
  std::cout<< "Using Port: " << Config::default_port << std::endl;
  std::cout << "Buffer Size: " << Config::buffer_size << std::endl;
  std::cout << "Connection Timeout: " << Config::connection_timeout << " ms"<< std::endl;
  std::cout << "Protocol Version: " << Config::protocol_version << std::endl;

  Socket serverSocket;
  if(!serverSocket.create() || !serverSocket.bind(Config::default_port)) {
    std::cerr << " Server Setup Failed. " << std::endl;
    return -1;
  }

  if(!serverSocket.listen()){
    std::cerr<< " Server Listen Failed. " << std::endl;
    return -1;
  }

  std::cout<< "Server is listening on port " << Config::default_port << std::endl;

  Socket *clientSocket = serverSocket.accept();
  if(clientSocket){
    std::cout << "Client Connected!" << std::endl;

    std::string receivedMessage;
    clientSocket->receive(receivedMessage);
    std::cout << "Received : "  << receivedMessage << std::endl;

    clientSocket->send("Hello From the server");

    delete clientSocket; // Clean up after client disconnects.
  }

  return 0;
}
