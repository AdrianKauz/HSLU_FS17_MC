cmake_minimum_required(VERSION 3.6)
project(Uebung6_1)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c includes/Address.h includes/Address.c includes/AddressConsoleIO.c includes/AddressConsoleIO.h includes/AddressFileIO.c includes/AddressFileIO.h)
add_executable(Uebung6_1 ${SOURCE_FILES})