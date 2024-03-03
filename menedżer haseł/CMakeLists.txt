cmake_minimum_required(VERSION 3.21)
project(Projekt)

set(CMAKE_CXX_STANDARD 23)

add_executable(Projekt main.cpp Haslo.cpp Haslo.h Szyfrowanie.cpp Szyfrowanie.h)
