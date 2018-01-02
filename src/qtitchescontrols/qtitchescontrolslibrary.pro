TEMPLATE = lib
TARGET = QtItchesControls
DESTDIR = $$PROJECT_LIBRARY_DIR
CONFIG += create_prf
QT = quick

HEADERS += \
    qtitchesblockview.h \
    qtitchescategorymodel.h

SOURCES += \
    qtitchesblockview.cpp \
    qtitchescategorymodel.cpp

OTHER_FILES += \
    qtitchescontrolslibrary.pri

include(../qtitchescore/qtitchescorelibrary.pri)
