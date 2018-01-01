TEMPLATE = lib
TARGET = QtItchesControls
DESTDIR = $$PROJECT_LIBRARY_DIR
CONFIG += create_prf
QT = quick

HEADERS += \
    qtitchesblockview.h

SOURCES += \
    qtitchesblockview.cpp

OTHER_FILES += \
    qtitchescontrolslibrary.pri

include(../qtitchescore/qtitchescorelibrary.pri)
