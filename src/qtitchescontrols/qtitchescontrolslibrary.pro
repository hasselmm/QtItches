TEMPLATE = lib
TARGET = QtItchesControls
DESTDIR = $$PROJECT_LIBRARY_DIR
OBJECTS_DIR = $${QT_ARCH}/qtitchescontrolslibrary
MOC_DIR = $$OBJECTS_DIR

CONFIG += create_prl
QT = quick

DEFINES += \
    QTITCHES_CONTROLS_EXPORT=Q_DECL_EXPORT

HEADERS += \
    qtitchesblockdroparea.h \
    qtitchesblockview.h \
    qtitchescategorymodel.h \
    qtitchescontrolsglobal.h

SOURCES += \
    qtitchesblockdroparea.cpp \
    qtitchesblockview.cpp \
    qtitchescategorymodel.cpp

OTHER_FILES += \
    qtitchescontrolslibrary.pri

include(../qtitchescore/qtitchescorelibrary.pri)
