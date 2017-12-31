import QtItches.Core 1.0
import QtQml 2.2

Block {
    property Script loop: Script {}
    readonly property var scripts: loop

    category: Block.ControlCategory
    connectors: Block.TopConnector
    parameters: ConstantParameter { string: qsTr("forever") }

    function run() {
        return loop.run();
    }

    Connections {
        target: loop
        onFinished: loop.run()
    }
}
