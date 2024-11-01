# Setup Details

## config/config.h
-- In config.h we define Config class that stores static configuration variables and a method to load values from a configuration file (eg. JSON);
## config/config.cpp
-- In config.cpp we initialize the static members of the config class and implement the load(). We use the JSON library, nlohmann, for demonstration.

### Objective of Config.
-- In config folder we set the parameters that is going to be used in entire project like default_port, buffer_size, connection_timeout.
Here the load method is provided to load the configuration from config.json or simmilar file to load the configuration giving it a leverage to choose different values but in case the file failed to load or if some configuration were missing then the default values will be considered.


## include/network/socket.h
-- In socket.h, we define a Socket class that will encapsulate basic socket operations, like creating a socket, binding, closing it, listen for the server and connect with the client.

## src/network/socket.cpp
-- Here we will be implementing the socket functions in socket.cpp We'll use standard POSIX socket libraries for cross platform compatibility.



