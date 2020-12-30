include(../qtitchescore/qtitchescorelibrary.pri)

CONFIG *= link_prl
QT *= quick

DEPENDPATH *= $$PWD
INCLUDEPATH *= $$PWD

linkSharedLibrary(QtItchesControls)
