cmake_minimum_required(VERSION 3.8)

add_library(${PROJECT_NAME} "dungeonator.c" "dungeonator.h")
target_include_directories(${PROJECT_NAME} PUBLIC ".")
