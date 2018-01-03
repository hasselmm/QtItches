import QtItches.Core 1.0
import QtQml 2.2

Block {
    id: thinkForSecs

    property alias text: textParameter.value
    property alias seconds: secondsParameter.value

    category: Block.LooksCategory

    ConstantParameter { string: qsTr("think") }
    StringParameter { id: textParameter }
    ConstantParameter { string: qsTr("for") }
    NumberParameter { id: secondsParameter; decimals: 1; number: 5 }
    ConstantParameter { string: qsTr("secs") }

    function run() {
        actor.think(text);
        timer.start();
    }

    Timer {
        id: timer

        interval: secondsParameter.number * 1000
        repeat: false

        onTriggered: {
            actor.think("");
            thinkForSecs.finished();
        }
    }
}
