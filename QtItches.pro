TEMPLATE = subdirs

SUBDIRS = src

!cross_compile {
    SUBDIRS += tests
    tests.depends = src
}

OTHER_FILES += \
    LICENSE \
    README.md \
    .gitignore \
    .qmake.conf \
    .travis/install_ndk.sh \
    .travis/install_qt.sh \
    .travis/qt.conf \
    .travis.yml

QML_IMPORT_PATH = $$PROJECT_IMPORTS_DIR
