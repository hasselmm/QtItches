import QtItches.Core 1.0
import QtQml 2.15

Block {
    id: doIfElse

    property alias condition: conditionParameter.value

    property Script then: Script {}
    property Script otherwise: Script {}
    property alias elseways: doIfElse.otherwise
    property alias _else: doIfElse.otherwise

    readonly property var scripts: [then, otherwise]
    property var scriptNames: [QT_TR_NOOP("else")]

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: QT_TR_NOOP("if") },
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

        function onFinished() {
            enabled = false;
            doIfElse.finished();
        }
    }
}
