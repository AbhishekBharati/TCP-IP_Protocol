#include "./config.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

// Initialize Static members :-
int Config::default_port = 8080;
int Config::buffer_size = 1024;
int Config::connection_timeout = 5000;
std::string Config::protocol_version = "1.0";

void Config::load(const std::string &filepath){
  try {
    std::ifstream config_file(filepath);
    if(!config_file.is_open()) {
      throw std::runtime_error("Unable to open config file.");
    }

    nlohmann::json config_json;
    config_file >> config_json;

    // Load settings from JSON, while error checking.
    if(config_json.contains("default_port")) {
      Config::default_port = config_json["default_port"].get<int>();
    }
    if(config_json.contains("buffer_size")) {
      Config::buffer_size = config_json["buffer_size"].get<int>();
    }
    if(config_json.contains("connection_timeout")) {
      Config::connection_timeout = config_json["connection_timeout"].get<int>();
    }
    if(config_json.contains("protocol_version")) {
      Config::protocol_version = config_json["protocol_version"].get<std::string>();
    }
  } catch (const std::exception &e){
    std::cerr << "Error loading configuration: " << e.what() << std::endl;
  }
}
