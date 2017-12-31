TEMPLATE = lib
CONFIG += plugin

QMAKE_MOC_OPTIONS += -Muri=QtItches.Core

SOURCES = qtitchescoreplugin.cpp
RESOURCES = qtitchescoreplugin.qrc
OBJECTS_DIR = qtitchescoreplugin
MOC_DIR = $$OBJECTS_DIR

include(qtitchescorelibrary.pri)
