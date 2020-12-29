import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.15

Rectangle {
    property font font: BlockView.editorFont
    property color textColor: BlockView.textColor

    property ChoiceParameter parameter

    color: Qt.darker(BlockView.shapeColor, 1.2)
    implicitWidth: label.implicitWidth + 6
    implicitHeight: label.implicitHeight + 2
    radius: 3

    Text {
        id: label

        anchors.centerIn: parent
        color: parent.textColor
        font.pixelSize: 12
        text: parameter && parameter.model[parameter.currentIndex] || ""
    }

    MouseArea {
        anchors.fill: parent
        onClicked: popupOverlay.show(parent, parameter.model, function selectItem(index) {
            parameter.currentIndex = index;
        })
    }
}
