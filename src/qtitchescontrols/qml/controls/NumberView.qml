import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.9

Rectangle {
    property NumberParameter parameter
    property font font: BlockView.font

    color: "#eeffffff"
    implicitWidth: Math.max(input.implicitWidth + 4, implicitHeight)
    implicitHeight: input.implicitHeight + 2
    radius: 3

    TextInput {
        id: input

        anchors.centerIn: parent
        font: parent.font
        inputMethodHints: Qt.ImhDigitsOnly
        text: parameter && parameter.number

        validator: DoubleValidator {
            id: validator

            decimals: parameter && parameter.decimals || 0
            bottom: parameter && parameter.lowestNumber || 0
            top: parameter && parameter.highestNumber || 0
        }

        onEditingFinished: parameter.number = parseFloat(text)
    }
}
