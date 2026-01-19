cmake_minimum_required(VERSION 3.10)

project(HuffmanCompressor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
    main.cpp
    src/HuffmanTree.cpp 
    src/Bitwriter.cpp
)

add_executable(huffman_app ${SOURCES})

target_include_directories(huffman_app PUBLIC .)