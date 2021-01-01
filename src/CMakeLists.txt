cmake_minimum_required(VERSION 3.8)

add_library(dungeonator "dungeonator.c" "dungeonator.h")
target_include_directories(dungeonator PUBLIC ".")
