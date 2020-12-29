import QtItches.Core 1.0

import QtQuick 2.15

Rectangle {
    id: contextChooser

    property int currentIndex: 1
    property Project project
    readonly property ScriptContext currentContext: project && project.contextes[currentIndex]

    function indexOf(context) {
        for (var i = 0, c = contextRepeater.count; i < c; ++i) {
            if (contextRepeater.itemAt(i).context === context)
                return i;
        }

        return -1;
    }

    color: "#10200000"

    Flow {
        anchors {
            fill: parent
            margins: milc(50)
        }

        spacing: milc(50)

        Repeater {
            id: contextRepeater

            model: contextChooser.project && contextChooser.project.contextes

            Rectangle {
                readonly property ScriptContext context: modelData
                readonly property bool isCurrentContext: contextChooser.currentIndex === model.index

                border { color: "#40200020"; width: 1 }
                color: isCurrentContext ? "#402000ff" : "#10200000"
                radius: milc(30)

                width: inch(0.5)
                height: inch(0.5)

                Column {
                    anchors {
                        fill: parent
                        margins: milc(20)
                    }

                    spacing: milc(50)

                    Image {
                        antialiasing: true
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                        width: parent.width
                        height: parent.height - parent.spacing - contextLabel.height
                        source: context.costumes && context.costumes[0] || ""
                    }

                    Text {
                        id: contextLabel

                        elide: Text.ElideRight
                        font.pixelSize: mil(110)
                        horizontalAlignment: Text.AlignHCenter
                        text: !model.index ? qsTr("Stage") : context.name || ""
                        width: parent.width
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: contextChooser.currentIndex = model.index
                }
            }
        }
    }
}
