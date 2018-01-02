import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.9

Item {
    property Parameter parameter

    implicitWidth: expressionView.implicitWidth
    implicitHeight: expressionView.implicitHeight

    BlockView {
        id: expressionView
        block: parameter && parameter.expression
    }
}
