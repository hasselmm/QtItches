import QtItches.Core 1.0
import QtQml 2.2

Block {
    id: doIfElse

    property alias condition: conditionParameter.value

    property Script then: Script {}
    property Script otherwise: Script {}
    property alias elseways: doIfElse.otherwise
    property alias _else: doIfElse.otherwise

    readonly property var scripts: [then, otherwise]
    property var scriptNames: [qsTr("else")]

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: qsTr("if") },
        BooleanParameter { id: conditionParameter }
    ]

    function run() {
        scriptMonitor.target = condition ? then : otherwise;
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
