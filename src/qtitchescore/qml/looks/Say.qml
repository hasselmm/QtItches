import QtItches.Core 1.0

Block {
    property alias text: textParameter.value

    category: Block.LooksCategory
    parameters: [
        ConstantParameter { string: qsTr("say:") },
        StringParameter { id: textParameter }
    ]

    function run() {
        actor.say(text);
        finished();
    }
}
