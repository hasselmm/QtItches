TEMPLATE = subdirs

SUBDIRS = \
    qtitchescorelibrary \
    qtitchescoreplugin \
    qtitchescorestaticplugin

qtitchescorelibrary.file = qtitchescorelibrary.pro

qtitchescoreplugin.file = qtitchescoreplugin.pro
qtitchescoreplugin.depends = qtitchescorelibrary

qtitchescorestaticplugin.file = qtitchescorestaticplugin.pro
qtitchescorestaticplugin.depends = qtitchescorelibrary
