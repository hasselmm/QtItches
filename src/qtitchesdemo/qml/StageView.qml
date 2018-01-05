import QtItches.Core 1.0 as Core
import QtItches.Controls 1.0

import QtQml.Models 2.3

import QtQuick 2.9
import QtQuick.Layouts 1.3

Rectangle {
    property Core.Stage stage

    border { color: "#40200020"; width: 1 }
    color: "#10200000"
    radius: 11

    implicitWidth: stageColumn.implicitWidth + 10
    implicitHeight: stageColumn.implicitHeight + 10

    Column {
        id: stageColumn

        anchors.centerIn: parent

        Text {
            font.bold: true
            text: stage.name
            bottomPadding: 5
        }

        Row {
            spacing: 10

            Repeater {
                model: stage.sprites

                Rectangle {
                    readonly property Core.Sprite sprite: modelData

                    border { color: "#40000020"; width: 1 }
                    color: "#10000020"
                    radius: 7

                    implicitWidth: spriteGrid.implicitWidth + 10
                    implicitHeight: spriteGrid.implicitHeight + 10

                    GridLayout {
                        id: spriteGrid

                        anchors.centerIn: parent

                        Text {
                            Layout.row: 0
                            Layout.fillWidth: true

                            font.bold: true
                            text: sprite.name
                            bottomPadding: 5
                        }

                        Image {
                            Layout.column: 1
                            Layout.row: 0
                            Layout.rowSpan: 4

                            rotation: sprite.direction - 90
                            source: sprite.costumes[0] || ""

                            MouseArea {
                                anchors.fill: parent
                                onClicked: sprite.clicked(parent)
                            }
                        }

                        Text {
                            Layout.row: 1

                            text: sprite.saying ? qsTr("says `%1'").arg(sprite.saying)
                                                : qsTr("says nothing")
                        }

                        Text {
                            Layout.row: 2

                            text: sprite.thinking ? qsTr("thinks `%1'").arg(sprite.thinking)
                                                  : qsTr("thinks nothing")
                        }

                        Text {
                            Layout.row: 3
                            Layout.fillHeight: true

                            bottomPadding: 10
                            font.pixelSize: 9
                            text: qsTr("x: %1; y: %2; direction: %3°").arg(sprite.x.toFixed(1)).arg(sprite.y.toFixed(1)).arg(sprite.direction.toFixed(1))
                        }

                        Row {
                            Layout.row: 4
                            Layout.columnSpan: 2

                            spacing: 5

                            Repeater {
                                model: sprite.scripts

                                Rectangle {
                                    readonly property Core.Script script: modelData

                                    border { color: "#40002000"; width: 1 }
                                    color: "#10020000"
                                    radius: 5

                                    implicitWidth: scriptColumn.implicitWidth + 10
                                    implicitHeight: scriptColumn.implicitHeight + 10

                                    ColumnLayout {
                                        id: scriptColumn

                                        anchors.centerIn: parent
                                        spacing: -1

                                        Repeater {
                                            id: blockRepeater

                                            model: script.blocks

                                            BlockView {
                                                Layout.fillWidth: true
                                                block: modelData
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
        }
    }
}
