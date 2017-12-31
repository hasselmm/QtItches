CONFIG *= link_prf
QT *= quick

DEPENDPATH *= $$PWD
INCLUDEPATH *= $$PWD

LIBS *= -L$$shadowed($$PWD)
LIBS *= -lQtItchesControls
