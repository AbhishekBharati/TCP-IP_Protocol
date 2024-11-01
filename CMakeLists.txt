cmake_minimum_required(VERSION 3.10)

#Project name and c++ standard :-
project(TCP-IP_Protocol)
set(CMAKE_CXX_STANDARD 17)

# Include directories for header files :-
include_directories(include)

# Add FetchContent for nlohmann/json
include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# Source files for the project :-
set(SRC
    src/main.cpp
    config/config.cpp
    src/network/socket.cpp
  )

# Create the executable from the specified sources
add_executable(TCP_Protocol ${SRC})

# Link nlohmann/json library :-
target_link_libraries(TCP_Protocol PRIVATE nlohmann_json::nlohmann_json)

# Link system libraries for socket functionality on Linux.
if(UNIX AND NOT APPLE)
    target_link_libraries(TCP_Protocol PRIVATE pthread)
endif()
