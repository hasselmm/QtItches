import QtItches.Core 1.0

SpriteBlock {
    property alias text: textParameter.value

    category: Block.LooksCategory
    parameters: [
        ConstantParameter { string: QT_TR_NOOP("say:") },
        StringParameter { id: textParameter }
    ]

    function run() {
        sprite.say(text);
        finished();
    }
}
