add_library(
    QtItchesCore SHARED
    qtitchesblock.cpp
    qtitchesblock.h
    qtitchesblocklibrary.cpp
    qtitchesblocklibrary.h
    qtitchesexpression.cpp
    qtitchesexpression.h
    qtitchesmetaenumiterator.cpp
    qtitchesmetaenumiterator.h
    qtitchesparameter.cpp
    qtitchesparameter.h
    qtitchesproject.cpp
    qtitchesproject.h
    qtitchesscript.cpp
    qtitchesscript.h
    qtitchesscriptcontext.cpp
    qtitchesscriptcontext.h
    qtitchessprite.cpp
    qtitchessprite.h
    qtitchesstage.cpp
    qtitchesstage.h
    qtitchesutils.cpp
    qtitchesutils.h
    )

target_compile_definitions(
    QtItchesCore
    PRIVATE -DQTITCHES_CORE_EXPORT=Q_DECL_EXPORT
    )

target_include_directories(
    QtItchesCore
    PUBLIC .
    )

target_link_libraries(
    QtItchesCore
    PUBLIC Qt5::Qml
    PRIVATE Qt5::QmlPrivate
    )

add_library(
    QtItchesCorePlugin MODULE
    qtitchescoreplugin.cpp
    qtitchescoreplugin.qrc
    )

set_target_properties(
    QtItchesCorePlugin PROPERTIES
    AUTOMOC_MOC_OPTIONS -Muri=QtItches.Core)

target_link_libraries(
    QtItchesCorePlugin
    PUBLIC QtItchesCore
    )

add_library(
    QtItchesCoreStaticPlugin STATIC
    qtitchescoreplugin.cpp
    qtitchescoreplugin.qrc
    )

set_target_properties(
    QtItchesCoreStaticPlugin PROPERTIES
    AUTOMOC_MOC_OPTIONS -Muri=QtItches.Core)

target_compile_definitions(
    QtItchesCoreStaticPlugin
    PRIVATE -DQT_STATICPLUGIN=1
    )

target_link_libraries(
    QtItchesCoreStaticPlugin
    PUBLIC QtItchesCore
    )

