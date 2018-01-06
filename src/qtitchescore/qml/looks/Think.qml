import QtItches.Core 1.0

SpriteBlock {
    property alias text: textParameter.value

    category: Block.LooksCategory
    parameters: [
        ConstantParameter { string: qsTr("think:") },
        StringParameter { id: textParameter }
    ]

    function run() {
        sprite.think(text);
        finished();
    }
}
