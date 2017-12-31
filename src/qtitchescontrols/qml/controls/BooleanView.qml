import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.9
BooleanShape {
    property BooleanParameter parameter

    fillColor: Qt.darker(_qtItches_blockView_.shapeColor, 1.2)
    implicitWidth: implicitHeight * 1.5
    implicitHeight: _qtItches_blockView_.font.pixelSize
}
