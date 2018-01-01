TEMPLATE = lib
CONFIG += plugin

SOURCES = qtitchescontrolsplugin.cpp
RESOURCES = qtitchescontrolsplugin.qrc
OBJECTS_DIR = qtitchescontrolsplugin

buildQmlPlugin(QtItches.Controls, 1.0)
include(qtitchescontrolslibrary.pri)
