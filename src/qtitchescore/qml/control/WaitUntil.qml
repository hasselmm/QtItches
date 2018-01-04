import QtItches.Core 1.0
import QtQml 2.2

Block {
    property alias expression: expressionParameter.value

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: qsTr("waitUntil") },
        BooleanParameter { id: expressionParameter }
    ]

    function run() {
        expressionMonitor.enabled = !expressionParameter.boolean;
        if (!expressionMonitor.enabled)
            finished();
    }

    function stop() {
        expressionMonitor.enabled = false;
        finished();
    }

    Connections {
        id: expressionMonitor

        enabled: false
        target: expressionParameter

        onBooleanChanged: run()
    }
}
