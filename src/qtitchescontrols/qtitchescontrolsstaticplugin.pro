TEMPLATE = lib
CONFIG += plugin static
DESTDIR = $$PROJECT_LIBRARY_DIR

QMAKE_MOC_OPTIONS += -Muri=QtItches.Controls

SOURCES = qtitchescontrolsplugin.cpp
RESOURCES = qtitchescontrolsplugin.qrc
OTHER_FILES = qtitchescontrolsstaticplugin.pri
OBJECTS_DIR = qtitchescontrolsstaticplugin
MOC_DIR = $$OBJECTS_DIR

include(qtitchescontrolslibrary.pri)
