TEMPLATE = lib
TARGET = QtItchesCore
DESTDIR = $$PROJECT_LIBRARY_DIR
CONFIG += create_prf
QT += qml_private

DEFINES += \
    QTITCHES_CORE_EXPORT=Q_DECL_EXPORT

HEADERS += \
    qtitchesblock.h \
    qtitchesblocklibrary.h \
    qtitchescoreglobal.h \
    qtitchesexpression.h \
    qtitchesmetaenumiterator.h \
    qtitchesparameter.h \
    qtitchesproject.h \
    qtitchesscript.h \
    qtitchesscriptcontext.h \
    qtitchessprite.h \
    qtitchesstage.h \
    qtitchesutils.h

SOURCES += \
    qtitchesblock.cpp \
    qtitchesblocklibrary.cpp \
    qtitchesexpression.cpp \
    qtitchesmetaenumiterator.cpp \
    qtitchesparameter.cpp \
    qtitchesproject.cpp \
    qtitchesscript.cpp \
    qtitchesscriptcontext.cpp \
    qtitchessprite.cpp \
    qtitchesstage.cpp \
    qtitchesutils.cpp

OTHER_FILES += \
    qtitchescorelibrary.pri
