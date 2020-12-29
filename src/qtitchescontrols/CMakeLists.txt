add_library(
    QtItchesControls SHARED
    qtitchesblockdroparea.cpp
    qtitchesblockdroparea.h
    qtitchesblockview.cpp
    qtitchesblockview.h
    qtitchescategorymodel.cpp
    qtitchescategorymodel.h
    qtitchescontrolsglobal.h
    )

target_compile_definitions(
    QtItchesControls
    INTERFACE -DQTITCHES_CONTROLS_EXPORT=Q_DECL_IMPORT
    PRIVATE -DQTITCHES_CONTROLS_EXPORT=Q_DECL_EXPORT
    )

target_include_directories(
    QtItchesControls
    PUBLIC .
    )

target_link_libraries(
    QtItchesControls
    PUBLIC QtItchesCore
    PUBLIC Qt5::Quick
    )

add_library(
    QtItchesControlsPlugin MODULE
    qtitchescontrolsplugin.cpp
    qtitchescontrolsplugin.qrc
    )

set_target_properties(
    QtItchesControlsPlugin PROPERTIES
    AUTOMOC_MOC_OPTIONS -Muri=QtItches.Controls)

target_link_libraries(
    QtItchesControlsPlugin
    PUBLIC QtItchesControls
    )

add_library(
    QtItchesControlsStaticPlugin STATIC
    qtitchescontrolsplugin.cpp
    qtitchescontrolsplugin.qrc
    )

set_target_properties(
    QtItchesControlsStaticPlugin PROPERTIES
    AUTOMOC_MOC_OPTIONS -Muri=QtItches.Controls)

target_compile_definitions(
    QtItchesControlsStaticPlugin
    PRIVATE -DQT_STATICPLUGIN=1
    )

target_link_libraries(
    QtItchesControlsStaticPlugin
    PUBLIC QtItchesControls
    )

