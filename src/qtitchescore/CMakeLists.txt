add_library(
    qtitchescore SHARED
    qtitchesactor.cpp
    qtitchesactor.h
    qtitchesblock.cpp
    qtitchesblock.h
    qtitchesexpression.cpp
    qtitchesexpression.h
    qtitchesparameter.cpp
    qtitchesparameter.h
    qtitchesscript.cpp
    qtitchesscript.h
    qtitchesstage.cpp
    qtitchesstage.h)

target_link_libraries(qtitchescore Qt5::Qml)
set_property(TARGET qtitchescore
    APPEND PROPERTY OUTPUT_NAME QtItchesCore)
set_property(TARGET qtitchescore
    APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/QtItches/Core>)

add_library(
    qtitchescoreplugin MODULE
    qtitchescoreplugin.cpp
    qtitchescoreplugin.qrc
    qmldir)

file(COPY qmldir DESTINATION "../../imports/QtItches/Core")

target_link_libraries(qtitchescoreplugin qtitchescore)
set_target_properties(qtitchescoreplugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "../../imports/QtItches/Core")
