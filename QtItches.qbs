import qbs 1.0

Project {
    name: "QtItches"

    Product {
        name: "qtitches"

        Export {
            Depends {
                name: "cpp"
            }

            cpp.exportedSymbolsCheckMode: "strict"
            cpp.allowUnresolvedSymbols: "false"
            cpp.cxxLanguageVersion: "c++14"

            Depends {
                name: "Android.ndk"
                condition: qbs.targetOS.contains("android")
            }

            Android.ndk.platform: "android-19"
            Android.ndk.appStl: "gnustl_shared"
        }
    }

    references: "src"
}
