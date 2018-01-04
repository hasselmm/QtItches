import QtItches.Core 1.0
import QtItches.Controls 1.0

BooleanShape {
    property BooleanParameter parameter

    fillColor: Qt.darker(BlockView.shapeColor, 1.2)
    implicitWidth: implicitHeight * 1.5
    implicitHeight: BlockView.font.pixelSize
}
