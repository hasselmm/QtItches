import QtItches.Core 1.0
import QtQml 2.2

Block {
    id: waitSecs

    property alias seconds: secondsParameter.value

    category: Block.ControlCategory

    parameters: [
        ConstantParameter { string: QT_TR_NOOP("wait") },
        NumberParameter { id: secondsParameter; decimals: 1; number: 5 },
        ConstantParameter { string: QT_TR_NOOP("secs") }
    ]

    function run() {
        timer.start();
    }

    function stop() {
        timer.stop();
        finished();
    }

    Timer {
        id: timer

        interval: secondsParameter.number * 1000
        repeat: false

        onTriggered: waitSecs.finished()
    }
}
