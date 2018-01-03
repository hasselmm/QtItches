import QtItches.Core 1.0

import QtQuick 2.9
import QtQuick.Shapes 1.0

Shape {
    property Block block
    property var scriptViews

    property real topPadding: 5
    property real leftPadding: 5
    property real rightPadding: 5
    property real bottomPadding: 5

    property bool hasTopConnector: block && (block.connectors & Block.TopConnector)
    property bool hasBottomConnector: block && (block.connectors & Block.BottomConnector)

    property int headerAlignment: Qt.AlignLeft | Qt.AlignVCenter

    property color fillColor: _qtItches_blockView_.shapeColor
    property color strokeColor: _qtItches_blockView_.borderColor

    Behavior on fillColor { ColorAnimation {} }
    Behavior on strokeColor { ColorAnimation {} }

    /*
    Rectangle {
        anchors.fill: parent
        border { width: 1; color: "#40ff0000" }
        color: "#20ff0000"
    }
     */
}
