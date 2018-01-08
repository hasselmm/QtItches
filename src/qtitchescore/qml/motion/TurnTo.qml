import QtItches.Core 1.0

SpriteBlock {
    property alias direction: directionParameter.value

    category: Block.MotionCategory

    ConstantParameter {
        string: QT_TR_NOOP("point into direction")
    }

    NumberParameter {
        id: directionParameter

        lowestNumber: -180
        highestNumber: 180

//        ProposedValue { name: QT_TR_NOOP("right"); value: 90 }
//        ProposedValue { name: QT_TR_NOOP("left"); value: -90 }
//        ProposedValue { name: QT_TR_NOOP("up"); value: 0 }
//        ProposedValue { name: QT_TR_NOOP("down"); value: 180 }
    }

    function run() {
        sprite.direction = direction;
        finished();
    }
}
