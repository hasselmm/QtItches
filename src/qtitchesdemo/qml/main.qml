import QtItches.Controls 1.0

import QtQuick 2.9
import QtQuick.Window 2.3

import "../projects"

Window {
    width: 1200
    height: 600
    visible: true

    Row {
        anchors {
            margins: 10
            fill: parent
        }

        spacing: 30

        BlockPicker {}
        StageView { project: Project1 {} }
        StageView { project: Project2 {} }
        StageView { project: Project3 {} }
    }

    PopupOverlay { id: popupOverlay }
}
