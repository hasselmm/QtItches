cmake_minimum_required(VERSION 3.1)
project(QtItches VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC on)
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 5.10 REQUIRED COMPONENTS Quick)

set(QML_IMPORT_PATH "${PROJECT_BINARY_DIR}/imports"
    CACHE STRING "Qt Creator 4.1 extra qml import paths")

string(APPEND CMAKE_MODULE_LINKER_FLAGS " -Wl,--no-undefined")
string(APPEND CMAKE_SHARED_LINKER_FLAGS " -Wl,--no-undefined")

add_subdirectory(src)
