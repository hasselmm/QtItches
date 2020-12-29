import QtItches.Core 1.0
import QtQml 2.15

Block {
    id: doRepeatUntil

    property alias condition: conditionParameter.value
    property Script loop: Script {}
    readonly property var scripts: loop

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: QT_TR_NOOP("repeat until") },
        BooleanParameter { id: conditionParameter }
    ]

    function run() {
        loopMonitor.enabled = true;
        loopMonitor.iterate();
    }

    function stop() {
        loopMonitor.enabled = false;
        loop.stop();
        finished();
    }

    Connections {
        id: loopMonitor

        function iterate() {
            if (!condition.boolean)
                loop.run();
            else
                doRepeatUntil.finished();
        }

        enabled: false
        target: loop

        function onFinished() {
            iterate();
        }
    }
}
