TEMPLATE = lib
CONFIG += plugin static
DESTDIR = $$PROJECT_LIBRARY_DIR
TARGET = qtitchescorestaticplugin
android: TARGET = $${TARGET}_$${QT_ARCH}

QMAKE_MOC_OPTIONS += -Muri=QtItches.Core

SOURCES = qtitchescoreplugin.cpp
RESOURCES = qtitchescoreplugin.qrc
OTHER_FILES = qtitchescorestaticplugin.pri
OBJECTS_DIR = $${QT_ARCH}/$${TARGET}
MOC_DIR = $$OBJECTS_DIR

include(qtitchescorelibrary.pri)
