#include <iostream>
#include "../config/config.h"

int main(){
  // Load configuration from file (if available)
  Config::load("../config/config.json");

  // Access config values and print them to check :-
  std::cout<< "Using Port: " << Config::default_port << std::endl;
  std::cout << "Buffer Size: " << Config::buffer_size << std::endl;
  std::cout << "Connection Timeout: " << Config::connection_timeout << " ms"<< std::endl;
  std::cout << "Protocol Version: " << Config::protocol_version << std::endl;

  return 0;
}
