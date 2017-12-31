TEMPLATE = lib
CONFIG += plugin

QMAKE_MOC_OPTIONS += -Muri=QtItches.Controls

SOURCES = qtitchescontrolsplugin.cpp
RESOURCES = qtitchescontrolsplugin.qrc
OBJECTS_DIR = qtitchescontrolsplugin

include(qtitchescontrolslibrary.pri)
