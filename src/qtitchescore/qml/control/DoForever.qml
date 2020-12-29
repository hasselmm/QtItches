import QtItches.Core 1.0
import QtQml 2.15

Block {
    property Script loop: Script {}
    readonly property var scripts: loop

    category: Block.ControlCategory
    connectors: Block.TopConnector
    parameters: ConstantParameter { string: QT_TR_NOOP("forever") }

    function run() {
        loopMonitor.enabled = true;
        loop.run();
    }

    function stop() {
        loopMonitor.enabled = false;
        loop.stop();
        finished();
    }

    Connections {
        id: loopMonitor

        enabled: false
        target: loop

        function onFinished() {
            loop.run();
        }
    }
}
