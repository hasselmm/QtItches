import QtItches.Core 1.0
import QtQml 2.2

Block {
    id: doIfElse

    property alias condition: conditionParameter.value

    property Script onTrue: Script {}
    property Script onFalse: Script {}
    readonly property var scripts: [onTrue, onFalse]
    property var scriptNames: [qsTr("else")]

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: qsTr("if") },
        BooleanParameter { id: conditionParameter }
    ]

    function run() {
        scriptMonitor.target = condition ? onTrue : onFalse;
        scriptMonitor.enabled = true;
        scriptMonitor.target.run();
    }

    function stop() {
        if (scriptMonitor.target && scriptMonitor.target.running)
            scriptMonitor.target.stop();
        else
            finished();
    }

    Connections {
        id: scriptMonitor

        enabled: false

        onFinished: {
            enabled = false;
            doIfElse.finished();
        }
    }
}
