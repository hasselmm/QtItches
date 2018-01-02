import QtItches.Core 1.0
import QtQml 2.2

Block {
    category: Block.EventsCategory
    connectors: Block.BottomConnector
    parameters: ConstantParameter { string: qsTr("when this sprite is clicked") }

    Connections {
        target: actor
        onClicked: script.run()
    }

    function run() {
        finished();
    }
}
