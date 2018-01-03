import QtItches.Core 1.0

Block {
    id: gotoXY

    property alias x: xParameter.value
    property alias y: yParameter.value

    category: Block.MotionCategory

    ConstantParameter { string: qsTr("go to x:") }
    NumberParameter { id: xParameter  }
    ConstantParameter { string: qsTr("y:") }
    NumberParameter { id: yParameter  }

    function run() {
        actor.position = Qt.point(x, y);
        gotoXY.finished();
    }
}