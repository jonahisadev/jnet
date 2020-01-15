cmake_minimum_required(VERSION 3.15)
project(jnet)

set(CMAKE_CXX_STANDARD 14)

add_library(jnet UdpServer.cpp UdpServer.h os.h UdpClient.cpp UdpClient.h)