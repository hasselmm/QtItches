import QtItches.Core 1.0
import QtItches.Controls 1.0
import QtQml.Models 2.3

import QtQuick 2.9
import QtQuick.Window 2.3

Window {
    width: 800
    height: 600
    visible: true

    Row {
        anchors {
            margins: 10
            fill: parent
        }

        spacing: 30

        StageView { stage: Stage1 {} }
        StageView { stage: Stage2 {} }
    }

    PopupOverlay { id: popupOverlay }
}
