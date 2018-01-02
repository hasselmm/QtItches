TEMPLATE = lib
TARGET = QtItchesCore
DESTDIR = $$PROJECT_LIBRARY_DIR
CONFIG += create_prf
QT += qml_private

HEADERS += \
    qtitchesactor.h \
    qtitchesblock.h \
    qtitchesblocklibrary.h \
    qtitchesexpression.h \
    qtitchesparameter.h \
    qtitchesscript.h \
    qtitchesstage.h \
    qtitchesutils.h

SOURCES += \
    qtitchesactor.cpp \
    qtitchesblock.cpp \
    qtitchesblocklibrary.cpp \
    qtitchesexpression.cpp \
    qtitchesparameter.cpp \
    qtitchesscript.cpp \
    qtitchesstage.cpp \
    qtitchesutils.cpp

OTHER_FILES += \
    qtitchescorelibrary.pri
