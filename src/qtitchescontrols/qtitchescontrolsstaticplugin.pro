TEMPLATE = lib
CONFIG += plugin static
DESTDIR = $$PROJECT_LIBRARY_DIR
TARGET = qtitchescontrolsstaticplugin
android: TARGET = $${TARGET}_$${QT_ARCH}

QMAKE_MOC_OPTIONS += -Muri=QtItches.Controls

SOURCES = qtitchescontrolsplugin.cpp
RESOURCES = qtitchescontrolsplugin.qrc
OTHER_FILES = qtitchescontrolsstaticplugin.pri
OBJECTS_DIR = $${QT_ARCH}/$${TARGET}
MOC_DIR = $$OBJECTS_DIR

include(qtitchescontrolslibrary.pri)
