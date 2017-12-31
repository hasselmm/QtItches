import QtItches.Core 1.0
import QtQuick 2.9

Rectangle {
    property font font: _qtItches_blockView_.editorFont
    property color textColor: _qtItches_blockView_.textColor

    property ChoiceParameter parameter

    color: Qt.darker(_qtItches_blockView_.shapeColor, 1.2)
    implicitWidth: label.implicitWidth + 6
    implicitHeight: label.implicitHeight + 2
    radius: 3

    Text {
        id: label

        anchors.centerIn: parent
        color: parent.textColor
        font.pixelSize: 12
        text: parameter.model[parameter.currentIndex] || ""
    }

    MouseArea {
        anchors.fill: parent
        onClicked: popupOverlay.show(parent, parameter.model, function selectItem(index) {
            parameter.currentIndex = index;
        })
    }
}
