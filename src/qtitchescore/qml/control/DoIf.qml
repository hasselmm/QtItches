import QtItches.Core 1.0
import QtQml 2.2

Block {
    id: doIf

    property alias condition: conditionParameter.value

    property Script onTrue: Script {}
    readonly property var scripts: onTrue

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: qsTr("if") },
        BooleanParameter { id: conditionParameter }
    ]

    function run() {
        if (condition) {
            scriptMonitor.enabled = true;
            onTrue.run();
        } else {
            finished();
        }
    }

    function stop() {
        if (onTrue.running)
            onTrue.stop();
        else
            finished();
    }

    Connections {
        id: scriptMonitor

        enabled: false
        target: onTrue

        onFinished: {
            enabled = false;
            doIf.finished();
        }
    }
}
