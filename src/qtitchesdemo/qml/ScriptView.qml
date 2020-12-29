import QtItches.Core 1.0 as Core
import QtItches.Controls 1.0

import QtQml.Models 2.15

import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: scriptView

    property Core.BlockLibrary library
    property Core.ScriptContext scriptContext

    border { color: "#40000020"; width: 1 }
    color: "#10000020"
    radius: 7

    Column {
        id: scriptColumn

        anchors.fill: parent
        spacing: 0

        Text {
            id: scriptLabel

            font {
                bold: true
                pixelSize: milc(240)
            }

            width: parent.width
            height: scriptLabel.implicitHeight + mil(150)

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: scriptContext.name !== undefined ? scriptContext.name : qsTr("Stage")
        }

        Flickable {
            width: parent.width
            height: parent.height - y

            clip: true
            contentWidth: scriptCanvas.implicitWidth
            contentHeight: scriptCanvas.implicitHeight

            Row {
                id: scriptCanvas

                spacing: 5

                Repeater {
                    model: scriptContext.scripts

                    Rectangle {
                        readonly property Core.Script script: modelData

                        border { color: "#40002000"; width: 1 }
                        color: "#10020000"
                        radius: 5

                        implicitWidth: blockColumn.implicitWidth + 10
                        implicitHeight: blockColumn.implicitHeight + 10

                        ColumnLayout {
                            id: blockColumn

                            anchors.centerIn: parent
                            spacing: -1

                            Repeater {
                                id: blockRepeater

                                model: script.blocks

                                BlockView {
                                    Layout.fillWidth: true
                                    block: modelData
                                    library: scriptView.library
                                }
                            }

                            Text {
                                Layout.alignment: Qt.AlignCenter
                                text: script.running ? qsTr("running") : qsTr("stopped")
                                font.pixelSize: 10
                                topPadding: 5
                            }
                        }
                    }
                }
            }
        }
    }
}
