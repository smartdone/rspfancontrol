cmake_minimum_required(VERSION 3.1)

project(rspfancontrol C)

add_library(ini 
    third_party/ini/ini.c
    third_party/ini/ini.h)

include_directories(third_party/ini/)

add_executable(rspfancontrol main.c)

target_link_libraries(rspfancontrol ini -lwiringPi -lpthread -lm -lcrypt -lrt)