import QtItches.Core 1.0
import QtQuick 2.9

Rectangle {
    property StringParameter parameter
    property font font: _qtItches_blockView_.font

    color: "#eeffffff"
    implicitWidth: Math.max(input.implicitWidth + 4, implicitHeight)
    implicitHeight: input.implicitHeight + 2
    radius: 3

    TextInput {
        id: input

        anchors.centerIn: parent
        font: parent.font

        maximumLength: parameter && parameter.maximumLength || 0
        text: parameter && parameter.string

        onEditingFinished: parameter.string = text
    }
}
