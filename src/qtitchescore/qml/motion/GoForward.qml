import QtItches.Core 1.0

Block {
    property alias steps: stepsParameter.value

    category: Block.MotionCategory

    ConstantParameter { string: qsTr("move") }
    NumberParameter { id: stepsParameter; value: 10; lowestNumber: 0; highestNumber: 1000 }
    ConstantParameter { string: qsTr("steps") }

    function run() {
        sprite.goForward(steps);
        finished();
    }
}
