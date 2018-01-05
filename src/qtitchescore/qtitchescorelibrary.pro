TEMPLATE = lib
TARGET = QtItchesCore
DESTDIR = $$PROJECT_LIBRARY_DIR
CONFIG += create_prf
QT += qml_private

HEADERS += \
    qtitchesblock.h \
    qtitchesblocklibrary.h \
    qtitchesexpression.h \
    qtitchesparameter.h \
    qtitchesproject.h \
    qtitchesscriptcontext.h \
    qtitchesscript.h \
    qtitchessprite.h \
    qtitchesstage.h \
    qtitchesutils.h

SOURCES += \
    qtitchesblock.cpp \
    qtitchesblocklibrary.cpp \
    qtitchesexpression.cpp \
    qtitchesparameter.cpp \
    qtitchesproject.cpp \
    qtitchesscriptcontext.cpp \
    qtitchesscript.cpp \
    qtitchessprite.cpp \
    qtitchesstage.cpp \
    qtitchesutils.cpp

OTHER_FILES += \
    qtitchescorelibrary.pri
