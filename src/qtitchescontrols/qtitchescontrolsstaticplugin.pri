LIBS *= -lqtitchescontrolsstaticplugin
include(qtitchescontrolslibrary.pri)

PRE_TARGETDEPS *= $$shadowed($$PWD/libqtitchescontrolsstaticplugin.a)
