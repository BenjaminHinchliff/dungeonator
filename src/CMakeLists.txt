cmake_minimum_required(VERSION 3.11)

add_library(${PROJECT_NAME} "dungeonator.c" "dungeonator.h")
target_include_directories(${PROJECT_NAME} PUBLIC ".")
