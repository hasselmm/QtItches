import QtItches.Core 1.0 as Core
import QtQuick 2.9

Rectangle {
    readonly property real spriteScale: Math.min(width / 500, height / 500)
    property Core.ScriptContext currentContext
    property Core.Project project

    signal spriteClicked(Core.Sprite sprite)

    Repeater {
        model: project && project.sprites

        Image {
            readonly property Core.Sprite sprite: modelData

            x: (stageView.width - width)/2 + sprite.x * stageView.spriteScale
            y: (stageView.height - height)/2 - sprite.y * stageView.spriteScale

            opacity: !currentContext || sprite === currentContext ? 1 : 0.3
            rotation: sprite.direction - 90
            source: sprite.costumes[0] || ""
            scale: stageView.spriteScale

            Behavior on opacity { NumberAnimation { duration: 100 } }

            Rectangle {
                border { width: 1; color: "#dd000000" }
                color: "#ddffffff"
                radius: sprite.thinking ? 8 : 2
                visible: thinkingLabel.text
                rotation: - parent.rotation

                implicitWidth: thinkingLabel.width + 6
                implicitHeight: thinkingLabel.height + 6

                Text {
                    id: thinkingLabel

                    anchors.centerIn: parent
                    text: sprite.saying || sprite.thinking || ""
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: spriteClicked(sprite)
            }
        }
    }
}
