import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQml.Models 2.3

import QtQuick 2.9
import QtQuick.Layouts 1.3

Rectangle {
    property Stage stage

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
                model: stage.actors

                Rectangle {
                    readonly property Actor actor: modelData

                    border { color: "#40000020"; width: 1 }
                    color: "#10000020"
                    radius: 7

                    implicitWidth: actorGrid.implicitWidth + 10
                    implicitHeight: actorGrid.implicitHeight + 10

                    GridLayout {
                        id: actorGrid

                        anchors.centerIn: parent

                        Text {
                            Layout.row: 0
                            Layout.fillWidth: true

                            font.bold: true
                            text: actor.name
                            bottomPadding: 5
                        }

                        Image {
                            Layout.column: 1
                            Layout.row: 0
                            Layout.rowSpan: 4

                            rotation: actor.direction - 90
                            source: actor.costumes[0] || ""

                            MouseArea {
                                anchors.fill: parent
                                onClicked: actor.clicked(parent)
                            }
                        }

                        Text {
                            Layout.row: 1

                            text: actor.saying ? qsTr("says `%1'").arg(actor.saying)
                                               : qsTr("says nothing")
                        }

                        Text {
                            Layout.row: 2

                            text: actor.thinking ? qsTr("thinks `%1'").arg(actor.thinking)
                                                 : qsTr("thinks nothing")
                        }

                        Text {
                            Layout.row: 3
                            Layout.fillHeight: true

                            bottomPadding: 10
                            font.pixelSize: 9
                            text: qsTr("x: %1; y: %2; direction: %3°").arg(actor.x.toFixed(1)).arg(actor.y.toFixed(1)).arg(actor.direction.toFixed(1))
                        }

                        Row {
                            Layout.row: 4
                            Layout.columnSpan: 2

                            spacing: 5

                            Repeater {
                                model: actor.scripts

                                Rectangle {
                                    readonly property Script script: modelData

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
