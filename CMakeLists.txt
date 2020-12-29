cmake_minimum_required(VERSION 3.14)
project(QtItches LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror=deprecated-declarations -Werror=conversion -Werror=format")
find_package(Qt5 5.15 REQUIRED COMPONENTS Quick)

add_subdirectory(src)

add_custom_target(
    travis SOURCES
    .travis.yml
    .travis/build.sh
    .travis/install_qt.sh
    .travis/install_ndk.sh
    .travis/qt.conf
    )
