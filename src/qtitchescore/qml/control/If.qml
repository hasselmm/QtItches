import QtItches.Core 1.0
import QtQml 2.2

Block {
    property alias condition: conditionParameter.value

    property Script onTrue: Script {}
    readonly property var scripts: onTrue

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: qsTr("if") },
        BooleanParameter { id: conditionParameter }
    ]

    function run() {
        if (condition)
            onTrue.run();
        else
            finished();
    }

    Connections {
        id: scriptMonitor

        target: onTrue
        onFinished: finished()
    }
}
