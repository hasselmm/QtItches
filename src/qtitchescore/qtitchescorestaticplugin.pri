QTITCHESCORE_STATICPLUGIN_TARGET = qtitchescorestaticplugin
android: QTITCHESCORE_STATICPLUGIN_TARGET = $${QTITCHESCORE_STATICPLUGIN_TARGET}_$${QT_ARCH}
PRE_TARGETDEPS *= $$PROJECT_LIBRARY_DIR/$${QMAKE_PREFIX_STATICLIB}$${QTITCHESCORE_STATICPLUGIN_TARGET}.$${QMAKE_EXTENSION_STATICLIB}
LIBS *= -L$${PROJECT_LIBRARY_DIR} -l$${QTITCHESCORE_STATICPLUGIN_TARGET}

include(qtitchescorelibrary.pri) # dependencies must occur after usage for static libraries
