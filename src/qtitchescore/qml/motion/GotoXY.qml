import QtItches.Core 1.0

SpriteBlock {
    id: gotoXY

    property alias x: xParameter.value
    property alias y: yParameter.value

    category: Block.MotionCategory

    ConstantParameter { string: qsTr("go to x:") }
    NumberParameter { id: xParameter  }
    ConstantParameter { string: qsTr("y:") }
    NumberParameter { id: yParameter  }

    function run() {
        sprite.position = Qt.point(x, y);
        gotoXY.finished();
    }
}
