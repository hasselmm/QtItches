TEMPLATE = subdirs

SUBDIRS = \
    src \
    tests

OTHER_FILES += \
    .gitignore \
    .qmake.conf \

tests.depends = src

QML_IMPORT_PATH = $$PROJECT_IMPORTS_DIR
