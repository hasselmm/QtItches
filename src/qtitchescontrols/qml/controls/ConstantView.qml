import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.9

Text {
    property ConstantParameter parameter

    color: BlockView.textColor
    font: BlockView.font
    text: parameter ? qsTr(parameter.string) : ""
}
