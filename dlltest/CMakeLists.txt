cmake_minimum_required(VERSION 3.10)

project(MyDLL)

add_library(MyDLL SHARED dll.c)

add_executable(Test
    main.c
    )