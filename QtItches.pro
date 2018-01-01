TEMPLATE = subdirs

SUBDIRS = \
    src \
    tests

OTHER_FILES += \
    .gitignore \
    .qmake.conf \

tests.depends = src
