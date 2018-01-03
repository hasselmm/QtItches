TEMPLATE = lib
CONFIG += plugin

SOURCES = qtitchescoreplugin.cpp
RESOURCES = qtitchescoreplugin.qrc
OBJECTS_DIR = qtitchescoreplugin
MOC_DIR = $$OBJECTS_DIR

QMAKE_RPATHDIR += ../../../lib
buildQmlPlugin(QtItches.Core, 1.0)
include(qtitchescorelibrary.pri)
