import QtItches.Core 1.0
import QtQml 2.2

SpriteBlock {
    id: sayForSecs

    property alias text: textParameter.value
    property alias seconds: secondsParameter.value

    category: Block.LooksCategory

    ConstantParameter { string: qsTr("say") }
    StringParameter { id: textParameter }
    ConstantParameter { string: qsTr("for") }
    NumberParameter { id: secondsParameter; decimals: 1; number: 5 }
    ConstantParameter { string: qsTr("secs") }

    function run() {
        sprite.say(text);
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

        onTriggered: {
            sprite.say("");
            sayForSecs.finished();
        }
    }
}
