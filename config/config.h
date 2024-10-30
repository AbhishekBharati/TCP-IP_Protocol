#ifndef CONFIG_H
#define CONFIG_H

#include <string>
using namespace std;

class Config {
  public :
    static int default_port;
    static int buffer_size;
    static int connection_timeout;
    static string protocol_version;

    // Method to load configuration from a file :-
    static void load(const string &filepath);

  private :
    // Private constructor to prevent instantiation
    Config() = default;
};

#endif // CONFIG_H
