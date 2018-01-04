import QtItches.Core 1.0
import QtQml 2.2

Block {
    id: doRepeat

    property alias count: countParameter.value
    property int currentIteration: 0
    property Script loop: Script {}
    readonly property var scripts: loop

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: qsTr("repeat") },
        NumberParameter { id: countParameter; number: 10  }
    ]

    function run() {
        loopMonitor.enabled = true;
        loopMonitor.iterate(0);
    }

    function stop() {
        loopMonitor.enabled = false;
        loop.stop();
        finished();
    }

    Connections {
        id: loopMonitor

        function iterate(iteration) {
            currentIteration = iteration;

            if (currentIteration < countParameter.number)
                loop.run();
            else
                doRepeat.finished();
        }

        enabled: false
        target: loop

        onFinished: iterate(currentIteration + 1)
    }
}
