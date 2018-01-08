include(../qtitchescore/qtitchescorelibrary.pri)

QT *= quick

DEPENDPATH *= $$PWD
INCLUDEPATH *= $$PWD

linkSharedLibrary(QtItchesControls)
