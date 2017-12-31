import qbs 1.0

Project {
    DynamicLibrary {
        name: "qtitchescontrols"

        files: [
            "qtitchesblockview.cpp",
            "qtitchesblockview.h",
        ]

        Depends { name: "qtitchescore" }
        Depends { name: "Qt"; submodules: ["quick"] }

        Export {
            Depends { name: "cpp" }
            Depends { name: "qtitchescore" }
            Depends { name: "Qt"; submodules: ["quick"] }

            cpp.includePaths: product.sourceDirectory
            cpp.rpaths: product.buildDirectory
        }
    }

    LoadableModule {
        name: "qtitchescontrolsplugin"

        files: [
            "qtitchescontrolsplugin.cpp",
            "qtitchescontrolsplugin.qrc",
        ]

        Depends { name: "qtitchescontrols" }
    }

    StaticLibrary {
        name: "qtitchescontrolsstaticplugin"

        files: [
            "qtitchescontrolsplugin.cpp",
            "qtitchescontrolsplugin.qrc",
        ]

        cpp.defines: "QT_STATICPLUGIN"
        Qt.core.pluginMetaData: ["uri=QtItches.Controls"]

        Depends { name: "qtitchescontrols" }
        Export { Depends { name: "qtitchescontrols" } }
    }
}
