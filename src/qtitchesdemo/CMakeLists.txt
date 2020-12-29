add_executable(
    QtItchesDemo
    main.cpp
    main.qrc
    )

target_link_libraries(
    QtItchesDemo
    PRIVATE QtItchesCoreStaticPlugin
    PRIVATE QtItchesControlsStaticPlugin
    )
