import QtItches.Core 1.0
import QtQml 2.2

Block {
    id: doIf

    property alias condition: conditionParameter.value

    property Script then: Script {}
    readonly property var scripts: then

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: qsTr("if") },
        BooleanParameter { id: conditionParameter }
    ]

    function run() {
        if (condition) {
            scriptMonitor.enabled = true;
            then.run();
        } else {
            finished();
        }
    }

    function stop() {
        if (then.running)
            then.stop();
        else
            finished();
    }

    Connections {
        id: scriptMonitor

        enabled: false
        target: then

        onFinished: {
            enabled = false;
            doIf.finished();
        }
    }
}
