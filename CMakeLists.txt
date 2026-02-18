cmake_minimum_required(VERSION 3.5)
project(store_app)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(store_app
    main.cpp
    mainwindow.cpp mainwindow.h
    udpbroadcaster.cpp udpbroadcaster.h
)

target_link_libraries(store_app Qt5::Widgets Qt5::Network)