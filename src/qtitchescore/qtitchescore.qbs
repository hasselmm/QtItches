import qbs 1.0

Project {
    DynamicLibrary {
        name: "qtitchescore"

        files: [
            "qtitchesactor.cpp",
            "qtitchesactor.h",
            "qtitchesblock.cpp",
            "qtitchesblock.h",
            "qtitchesexpression.cpp",
            "qtitchesexpression.h",
            "qtitchesparameter.cpp",
            "qtitchesparameter.h",
            "qtitchesscript.cpp",
            "qtitchesscript.h",
            "qtitchesstage.cpp",
            "qtitchesstage.h",
        ]

        Depends { name: "qtitches" }
        Depends { name: "Qt"; submodules: ["qml"] }

        Export {
            Depends { name: "cpp" }
            Depends { name: "qtitches" }
            Depends { name: "Qt"; submodules: ["qml"] }

            cpp.includePaths: product.sourceDirectory
            cpp.rpaths: product.buildDirectory
        }
    }

    LoadableModule {
        name: "qtitchescoreplugin"

        files: [
            "qtitchescoreplugin.cpp",
            "qtitchescoreplugin.qrc",
        ]

        Qt.core.pluginMetaData: ["uri=QtItches.Core"]

        Depends { name: "qtitchescore" }
    }

    StaticLibrary {
        name: "qtitchescorestaticplugin"

        files: [
            "qtitchescoreplugin.cpp",
            "qtitchescoreplugin.qrc",
        ]

        cpp.defines: "QT_STATICPLUGIN"
        Qt.core.pluginMetaData: ["uri=QtItches.Core"]

        Depends { name: "qtitchescore" }
        Export { Depends { name: "qtitchescore" } }
    }
}
