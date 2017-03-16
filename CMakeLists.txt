cmake_minimum_required(VERSION 3.6)
project(blobwar)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    shmem.cc
    main.cc
    board.cc
    bidiarray.cc
    rollover.cc
    mouse.cc
    blobwar.cc
    image.cc
    network.cc
    blob.cc
    launchStrategy.cc
    widget.cc
    font.cc
    server/server.cc
    server/rules.cc
    label.cc
    button.cc
    rules.cc
    strategy.cc)
add_executable(blobwar ${SOURCE_FILES})
