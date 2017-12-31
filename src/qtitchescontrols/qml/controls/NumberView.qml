import QtItches.Core 1.0
import QtQuick 2.9

Rectangle {
    property NumberParameter parameter
    property font font: _qtItches_blockView_.font

    color: "#eeffffff"
    implicitWidth: Math.max(input.implicitWidth + 4, implicitHeight)
    implicitHeight: input.implicitHeight + 2
    radius: 3

    TextInput {
        id: input

        anchors.centerIn: parent
        font: parent.font
        inputMethodHints: Qt.ImhDigitsOnly
        text: parameter.number

        validator: DoubleValidator {
            id: validator

            decimals: parameter.decimals
            bottom: parameter.lowestNumber
            top: parameter.highestNumber
        }

        onEditingFinished: parameter.number = parseFloat(text)
    }
}
