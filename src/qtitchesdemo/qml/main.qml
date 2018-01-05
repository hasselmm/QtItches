import QtItches.Core 1.0 as Core
import QtItches.Controls 1.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.3

import "../projects" as Projects

Window {
    readonly property alias currentProject: scriptView.project

    function mm(x) { return x * Screen.pixelDensity; }
    function mil(x) { return mm(x) * 0.0254; }

    width: 1200
    height: 600
    visible: true

    StageView {
        id: stageView

        width: parent.width - (scriptView.width + blockPicker.width) * Math.pow(scriptView.opacity, 0.8)
        height: parent.height

        enabled: !maximizeScriptView.checked
        opacity: enabled ? 1 : 0
        visible: opacity > 0
        z: scriptView.opacity < 1 ? 1 : 0

        project: currentProject

        Button {
            id: maximizeCanvas
            checkable: true
            text: "maximize"
        }

        Row {
            anchors.right: parent.right

            Button {
                text: "start"
                onClicked: currentProject.flagClicked(this);
            }

            Button {
                text: "stop"
                onClicked: currentProject.stop()
            }
        }

        Behavior on opacity { NumberAnimation {} }
    }

    ScriptView {
        id: scriptView

        anchors.right: blockPicker.left
        width: (parent.width - blockPicker.width)/(stageView.opacity + 1)

        enabled: !maximizeCanvas.checked
        opacity: enabled ? 1 : 0
        visible: opacity > 0
        z: stageView.opacity < 1 ? 1 : 0

        project: Projects.Project3 {}

        Button {
            id: maximizeScriptView

            anchors.right: parent.right
            checkable: true
            text: "maximize"
        }

        Behavior on opacity { NumberAnimation {} }
    }

    BlockPicker {
        id: blockPicker

        anchors.right: parent.right
        height: parent.height

        enabled: scriptView.enabled
        opacity: scriptView.opacity
        visible: opacity > 0
    }

    PopupOverlay { id: popupOverlay }
}
