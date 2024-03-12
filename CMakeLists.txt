cmake_minimum_required(VERSION 3.12)
project(rd-kits)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_INSTALL_INCLUDEDIR /usr/local/include/${PROJECT_NAME})

# Install headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


