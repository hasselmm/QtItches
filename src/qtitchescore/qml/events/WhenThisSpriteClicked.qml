import QtItches.Core 1.0
import QtQml 2.15

Block {
    category: Block.EventsCategory
    connectors: Block.BottomConnector
    parameters: ConstantParameter { string: QT_TR_NOOP("when this sprite is clicked") }

    function run() {
        finished();
    }

    Connections {
        target: sprite

        onClicked: {
            if (script)
                script.run();
        }
    }
}
