TEMPLATE = lib
TARGET = QtItchesCore

CONFIG += create_prf
QT += qml

HEADERS += \
    qtitchesactor.h \
    qtitchesblock.h \
    qtitchesexpression.h \
    qtitchesparameter.h \
    qtitchesscript.h \
    qtitchesstage.h

SOURCES += \
    qtitchesactor.cpp \
    qtitchesblock.cpp \
    qtitchesexpression.cpp \
    qtitchesparameter.cpp \
    qtitchesscript.cpp \
    qtitchesstage.cpp

OTHER_FILES += \
    qtitchescorelibrary.pri
