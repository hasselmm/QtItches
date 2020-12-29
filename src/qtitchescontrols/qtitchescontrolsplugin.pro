TEMPLATE = lib
CONFIG += plugin

SOURCES = qtitchescontrolsplugin.cpp
RESOURCES = qtitchescontrolsplugin.qrc
OBJECTS_DIR = $${QT_ARCH}/qtitchescontrolsplugin
MOC_DIR = $$OBJECTS_DIR

QMAKE_RPATHDIR += ../../../lib
buildQmlPlugin(QtItches.Controls, 1.0)
include(qtitchescontrolslibrary.pri)
