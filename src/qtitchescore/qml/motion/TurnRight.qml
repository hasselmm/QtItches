import QtItches.Core 1.0

SpriteBlock {
    property alias angle: angleParameter.value

    category: Block.MotionCategory

    ConstantParameter { string: QT_TR_NOOP("turn right") }
    NumberParameter { id: angleParameter; value: 90; lowestNumber: 0; highestNumber: 359 }
    ConstantParameter { string: QT_TR_NOOP("degrees") }

    function run() {
        sprite.direction += angle;
        finished();
    }
}
