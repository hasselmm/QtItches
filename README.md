# QtItches

This is an alternative implementation of [MIT Scratch](https://scratch.mit.edu/)
using [Qt](https://www.qt.io/download-open-source/) and QML.

## Motivation

Initial motivation to start this project was to allow better hardware with
educational toys like Bluetooth controlled robots. Another goal is to provide
better support for mobile devices than with web, or even Flash interfaces.

## Licensing

[This project is licensed](LICENSE) to you under the terms of the GNU General
Public License to strongly encourage cooperation. Feel free to contact me if
this license doesn't work for you.

## Requirements

- A C++ compiler with decent support for C++14.
- [Qt 5.10](https://www.qt.io/download-open-source/) for
  [QtQuick.Shapes](http://blog.qt.io/blog/2017/07/07/let-there-be-shapes/)
  support.
- The [Android NDK](https://developer.android.com/ndk/) for Android builds.
- XCode for iOS builds.

## Build instructions

Simply open QtItches.pro in QtCreator and follow the usual steps, or directly
run your target platform's qmake on that file.
