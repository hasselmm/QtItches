CONFIG *= link_prf
QT *= qml

DEPENDPATH *= $$PWD
INCLUDEPATH *= $$PWD

LIBS *= -L$$shadowed($$PWD)
LIBS *= -lQtItchesCore
