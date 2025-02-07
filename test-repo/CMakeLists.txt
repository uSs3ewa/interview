cmake_minimum_required(VERSION 3.24.2)
project(testproj CXX)

add_executable(${PROJECT_NAME} 
  main.cpp
  candle.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
