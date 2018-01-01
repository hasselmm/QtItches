CONFIG += testcase
QT += testlib

exists($${TARGET}.cpp): SOURCES = $${TARGET}.cpp
exists($${TARGET}.qrc): RESOURCES += $${TARGET}.qrc
