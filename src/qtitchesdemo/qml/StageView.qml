import QtItches.Core 1.0 as Core
import QtQuick 2.9

Rectangle {
    readonly property real spriteScale: Math.min(width / 500, height / 500)
    property Core.Project project

    Repeater {
        model: project && project.sprites

        Image {
            readonly property Core.Sprite sprite: modelData

            x: (stageView.width - width)/2 + sprite.x * stageView.spriteScale
            y: (stageView.height - height)/2 - sprite.y * stageView.spriteScale

            rotation: sprite.direction - 90
            source: sprite.costumes[0] || ""
            scale: stageView.spriteScale

            Rectangle {
                visible: thinkingLabel.text
                color: "#ddffffff"
                radius: sprite.thinking ? 8 : 2
                border { width: 1; color: "#dd000000" }
                implicitWidth: thinkingLabel.width + 6
                implicitHeight: thinkingLabel.height + 6
                rotation: - parent.rotation
                Text { id: thinkingLabel; text: sprite.saying || sprite.thinking || ""; anchors.centerIn: parent }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: sprite.clicked(parent)
            }
        }
    }
}
