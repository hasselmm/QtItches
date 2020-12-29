import QtItches.Core 1.0
import QtQml 2.15

Block {
    category: Block.EventsCategory
    connectors: Block.BottomConnector

    ConstantParameter {
        string: QT_TR_NOOP("when green flag clicked")
    }

    Connections {
        target: project

        function onFlagClicked() {
            script.stop();
            script.run();
        }
    }

    function run() {
        finished();
    }
}
