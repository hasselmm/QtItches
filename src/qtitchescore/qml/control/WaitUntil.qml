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
        expression.enabled = !expressionParameter.boolean;
        if (!expression.enabled)
            finished();
    }

    Connections {
        id: expressionMonitor

        target: expressionParameter
        onBooleanChanged: run()
    }
}
