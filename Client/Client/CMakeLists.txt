# CMakeList.txt : CMake project for Client, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Client "Client.cpp" "Client.h")

# TODO: Add tests and install targets if needed.
if(WIN32)
  target_link_libraries(Client wsock32 ws2_32)
endif()