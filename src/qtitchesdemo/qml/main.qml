import QtItches.Controls 1.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.3

import "../projects" as Projects

Window {
    function mm(x) { return x * Screen.pixelDensity; }
    function mmc(x) { return Math.ceil(mm(x)); }

    function inch(x) { return mm(x * 25.4); }
    function inchc(x) { return Math.ceil(inch(x)); }

    function mil(x) { return inch(x / 1000); }
    function milc(x) { return Math.ceil(mil(x)); }

    title: currentProject.name
    width: 1200
    height: 600
    visible: true

    Timer {
        id: delayBehaviorsOnStartup

        interval: 150
        repeat: false
        running: true
    }

    StageView {
        id: stageView

        currentContext: !maximizeCanvas.checked && project && !project.running && contextChooser.currentContext || null
        project: currentProject

        width: (parent.width - blockPicker.width * scriptView.opacity) / (1 + Math.pow(scriptView.opacity, 0.8))
        height: parent.height - inch(0.6) * Math.pow(contextChooser.opacity, 0.8)

        clip: true
        enabled: !maximizeScriptView.checked
        opacity: enabled ? 1 : 0
        visible: opacity > 0
        z: scriptView.opacity < 1 ? 1 : 0

        Behavior on opacity { NumberAnimation {} }

        Button {
            id: maximizeCanvas
            checkable: true
            text: "maximize"
        }

        Row {
            anchors.right: parent.right

            Button {
                checked: currentProject && currentProject.running
                text: "start"

                onClicked: currentProject.flagClicked(this);
            }

            Button {
                enabled: currentProject && currentProject.running
                text: "stop"

                onClicked: currentProject.stop()
            }
        }

        onSpriteClicked: {
            if (project.running) {
                sprite.clicked(stageView);
                return;
            }

            var i = contextChooser.indexOf(sprite);
            if (i >= 0)
                contextChooser.currentIndex = i;
        }
    }

    ContextChooser {
        id: contextChooser

        anchors.bottom: parent.bottom
        width: maximizeScriptView.checked ? inch(0.6) : (parent.width - blockPicker.width)/2
        height: maximizeScriptView.checked ? parent.height : inch(0.6)

        Behavior on width { NumberAnimation {} enabled: !delayBehaviorsOnStartup.running }
        Behavior on height { NumberAnimation {} enabled: !delayBehaviorsOnStartup.running }

        enabled: !maximizeCanvas.checked
        opacity: enabled ? 1 : 0
        visible: opacity > 0
        z: stageView.opacity < 1 ? 1 : 0

        Behavior on opacity { NumberAnimation {} }

        project: currentProject
    }

    ScriptView {
        id: scriptView

        anchors.right: blockPicker.left
        width: parent.width - blockPicker.width - contextChooser.width
        height: parent.height

        enabled: !maximizeCanvas.checked
        opacity: enabled ? 1 : 0
        visible: opacity > 0
        z: stageView.opacity < 1 ? 1 : 0

        Behavior on opacity { NumberAnimation {} }

        scriptContext: contextChooser.currentContext
        Projects.Project3 { id: currentProject } // FIXME: figure out why the project must be instantiated within ScriptView

        Button {
            id: maximizeScriptView

            anchors.right: parent.right
            checkable: true
            text: "maximize"
        }

    }

    BlockPicker {
        id: blockPicker

        anchors.right: parent.right
        height: parent.height

        enabled: scriptView.enabled
        opacity: scriptView.opacity
        visible: opacity > 0

        context: contextChooser.currentContext
    }

    PopupOverlay { id: popupOverlay }
}
