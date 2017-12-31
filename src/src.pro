TEMPLATE = subdirs

SUBDIRS = \
    qtitchescontrols \
    qtitchescore \
    qtitchesdemo

qtitchescontrols.depends = qtitchescore
qtitchesdemo.depends = qtitchescontrols
