TEMPLATE = lib
TARGET = QtItchesControls
DESTDIR = $$PROJECT_LIBRARY_DIR
CONFIG += create_prf
QT = quick

HEADERS += \
    qtitchesblockdroparea.h \
    qtitchesblockview.h \
    qtitchescategorymodel.h

SOURCES += \
    qtitchesblockdroparea.cpp \
    qtitchesblockview.cpp \
    qtitchescategorymodel.cpp

OTHER_FILES += \
    qtitchescontrolslibrary.pri

include(../qtitchescore/qtitchescorelibrary.pri)
