add_library(
    qtitchescontrols SHARED
    qtitchesblockview.cpp
    qtitchesblockview.h
    )

target_link_libraries(qtitchescontrols qtitchescore Qt5::Quick)

add_library(
    qtitchescontrolsplugin MODULE
    qtitchescontrolsplugin.cpp
    qtitchescontrolsplugin.qrc
    )

file(COPY qmldir DESTINATION "../../imports/QtItches/Controls")

target_link_libraries(qtitchescontrolsplugin qtitchescontrols)
set_target_properties(qtitchescontrolsplugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "../../imports/QtItches/Controls")
