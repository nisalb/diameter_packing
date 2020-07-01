cmake_minimum_required(VERSION 3.2)

project(
  diameter_binpacking
  VERSION 2.0
  LANGUAGES C)

add_executable(test src/test.c src/avp.c src/msg.c)
