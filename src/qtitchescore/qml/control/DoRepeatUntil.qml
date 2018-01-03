import QtItches.Core 1.0
import QtQml 2.2

Block {
    property alias condition: conditionParameter.value
    property Script loop: Script {}
    readonly property var scripts: loop

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: qsTr("repeat until") },
        BooleanParameter { id: conditionParameter }
    ]

    function run() {
        loopMonitor.iterate(0);
    }

    Connections {
        id: loopMonitor

        function iterate() {
            if (!condition.boolean)
                loop.run();
            else
                finished();
        }

        target: loop
        onFinished: iterate()
    }
}
