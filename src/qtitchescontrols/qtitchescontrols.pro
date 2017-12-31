TEMPLATE = subdirs

SUBDIRS = \
    qtitchescontrolslibrary \
    qtitchescontrolsplugin \
    qtitchescontrolsstaticplugin

qtitchescontrolslibrary.file = qtitchescontrolslibrary.pro

qtitchescontrolsplugin.file = qtitchescontrolsplugin.pro
qtitchescontrolsplugin.depends = qtitchescontrolslibrary

qtitchescontrolsstaticplugin.file = qtitchescontrolsstaticplugin.pro
qtitchescontrolsstaticplugin.depends = qtitchescontrolslibrary
