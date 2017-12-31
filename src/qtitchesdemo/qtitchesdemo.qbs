import qbs 1.0

Project {
    Application {
        name: "qtitchesdemo"

        files: [
            "main.cpp",
            "main.qrc",
        ]

        Depends { name: "qtitchescorestaticplugin" }
        Depends { name: "qtitchescontrolsstaticplugin" }
    }

    AndroidApk {
        name: "qtitchesdemo.apk"
        packageName: "de.taschenorakel.qtitches.demo"

        files: [
            "android/AndroidManifest.xml"
        ]
    }
}
