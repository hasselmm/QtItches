import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.15

Rectangle {
    property StringParameter parameter
    property font font: BlockView.font

    color: dropArea.pendingDropAction ? "#eeff0000" : "#eeffffff" // FIXME: drop indication color
    Behavior on color { ColorAnimation {} }

    implicitWidth: Math.max(input.implicitWidth + 4, implicitHeight)
    implicitHeight: input.implicitHeight + 2
    radius: 3


    TextInput {
        id: input

        anchors.centerIn: parent
        font: parent.font

        color: dropArea.pendingDropAction ? "white" : "black" // FIXME: drop indication color
        Behavior on color { ColorAnimation {} }

        maximumLength: parameter && parameter.maximumLength || 0
        text: parameter && parameter.string

        onEditingFinished: parameter.string = text
    }

    BlockDropArea {
        id: dropArea

        anchors {
            fill: parent
            margins: -10
        }

        acceptedDropActions: {
            return BlockDropArea.ApplyStringExpression |
                             BlockDropArea.ApplyNumberExpression |
                             BlockDropArea.ApplyBooleanExpression
        }

        onTypeInfoDropped: parameter.value = BlockView.createBlock(typeInfo)
    }
}
