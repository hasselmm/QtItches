import QtItches.Core 1.0

SpriteBlock {
    property alias steps: stepsParameter.value

    category: Block.MotionCategory

    ConstantParameter { string: QT_TR_NOOP("move") }
    NumberParameter { id: stepsParameter; value: 10; lowestNumber: 0; highestNumber: 1000 }
    ConstantParameter { string: QT_TR_NOOP("steps") }

    function run() {
        sprite.goForward(steps);
        finished();
    }
}
