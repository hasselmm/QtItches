import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.9
import QtQuick.Layouts 1.3

ColumnLayout {
    id: blockPicker

    property BlockLibrary library

    spacing: 0//15

    width: 150
    height: parent.height

    Rectangle {
        Layout.fillWidth: true

        radius: 3
        color: "#10000000"
        implicitWidth: categorySelector.implicitWidth + 10
        implicitHeight: categorySelector.implicitHeight + 10

        GridLayout {
            id: categorySelector

            property int currentCategory: Block.MotionCategory

            Layout.fillWidth: true

            anchors.centerIn: parent
            rows: Math.ceil(categoryRepeater.count / 2)
            flow: GridLayout.TopToBottom
            rowSpacing: 2

            Repeater {
                id: categoryRepeater

                model: CategoryModel {}

                MouseArea {
                    readonly property bool isCurrentCategory: model.category === categorySelector.currentCategory

                    Layout.fillWidth: true

                    implicitWidth: categoryLabel.implicitWidth + 4
                    implicitHeight: categoryLabel.implicitHeight + 4

                    Rectangle {
                        color: model.color
                        radius: isCurrentCategory ? 2 : 1
                        width: isCurrentCategory ? parent.width : 6
                        height: parent.height

                        Behavior on radius { NumberAnimation { duration: 100 } }
                        Behavior on width { NumberAnimation { duration: 100 } }
                    }

                    Text {
                        id: categoryLabel

                        color: isCurrentCategory ? "white" : "black"
                        leftPadding: 10
                        font.pixelSize: 11
                        height: parent.height
                        text: model.name
                        verticalAlignment: Qt.AlignVCenter

                        Behavior on color { ColorAnimation { duration: 100 } }
                    }

                    onClicked: categorySelector.currentCategory = model.category
                }
            }
        }
    }

    ListView {
        id: libraryView

        Layout.fillWidth: true
        Layout.fillHeight: true

        clip: true
        spacing: 0
        model: blockPicker.library

        delegate: Item {
            width: libraryView.width
            height: (blockView.implicitHeight + 4) * Math.pow(opacity, 1.2)
            opacity: blockView.block.available &&
                     blockView.block.category === categorySelector.currentCategory ? 1 : 0

            Behavior on opacity { NumberAnimation { duration: 100 } }

            BlockView {
                id: blockView

                block: model.prototype
                library: blockPicker.library

                enabled: false
            }

            Drag.active: dragArea.drag.active
            Drag.dragType: Drag.Automatic
            Drag.proposedAction: Qt.CopyAction
            Drag.supportedActions: Qt.CopyAction

            MouseArea {
                id: dragArea

                property real dx0: parent.x
                property real dy0: parent.y

                anchors.fill: parent
                drag.target: parent

                onPressed: {
                    dx0 = parent.x; // store item position to work around QTBUG-65597
                    dy0 = parent.y;

                    parent.Drag.mimeData = blockView.createMimeData(model.typeInfo);
                    parent.Drag.hotSpot = Qt.point(mouse.x, mouse.y);
                    parent.grabToImage(function(result) {
                        parent.Drag.imageSource = result.url;
                    });
                }
                onReleased: {
                    parent.x = dx0; // restore item position to work around QTBUG-65597
                    parent.y = dy0;
                }
            }
        }
    }
}
