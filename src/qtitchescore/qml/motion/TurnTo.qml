import QtItches.Core 1.0

Block {
    property alias direction: directionParameter.value

    category: Block.MotionCategory

    ConstantParameter {
        string: qsTr("point in direction")
    }

    NumberParameter {
        id: directionParameter

        lowestNumber: -180
        highestNumber: 180

//        ProposedValue { name: qsTr("right"); value: 90 }
//        ProposedValue { name: qsTr("left"); value: -90 }
//        ProposedValue { name: qsTr("up"); value: 0 }
//        ProposedValue { name: qsTr("down"); value: 180 }
    }

    function run() {
        actor.direction = direction;
        finished();
    }
}
