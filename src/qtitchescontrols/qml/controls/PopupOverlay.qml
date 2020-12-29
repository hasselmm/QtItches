import QtQuick 2.15

Rectangle {
    id: popupOverlay

    anchors.fill: parent
    color: "#40000020"
    enabled: false
    opacity: enabled ? 1 : 0

    Behavior on opacity {
        NumberAnimation { duration: 100 }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: popupOverlay.enabled = false
    }

    Rectangle {
        id: popupMenu

        property var callback
        property font font
        property point origin
        property Item parentItem
        property color textColor

        x: Math.min(origin.x, popupOverlay.width - implicitWidth)
        y: origin.y - (implicitHeight - (parentItem && parentItem.implicitHeight))/2

        implicitWidth: popupColumn.implicitWidth + 6
        implicitHeight: popupColumn.implicitHeight + 2

        Column {
            id: popupColumn

            anchors.centerIn: parent

            Repeater {
                id: popupRepeater

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: popupMenu.textColor
                    font: popupMenu.font
                    text: modelData

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            popupOverlay.enabled = false;

                            if (popupMenu.callback)
                                popupMenu.callback(model.index);
                        }
                    }
                }
            }
        }

    }

    function show(parent, model, callback) {
        popupRepeater.model = model;

        popupMenu.callback = callback;
        popupMenu.color = parent.color;
        popupMenu.font = parent.font;
        popupMenu.origin = parent.mapToItem(popupOverlay, 0, 0);
        popupMenu.parentItem = parent;
        popupMenu.textColor = parent.textColor;

        popupOverlay.enabled = true;
    }
}
