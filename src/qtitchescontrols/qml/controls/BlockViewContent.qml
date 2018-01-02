import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.9
import QtQuick.Layouts 1.3

ColumnLayout {
    property Block block
    property BlockShape shape

    readonly property var scriptViews: {
        var views = [];

        for (var i = 0; i < scriptRepeater.count; ++i)
            views.push(scriptRepeater.itemAt(i))

        return views;
    }

    spacing: 0

    RowLayout {
        Layout.alignment: shape && shape.headerAlignment || 0
        Layout.leftMargin: shape && shape.leftPadding || 0
        Layout.topMargin: shape && shape.topPadding || 0
        Layout.rightMargin: shape && shape.rightPadding || 0
        Layout.bottomMargin: shape && shape.bottomPadding || 0

        spacing: 5

        Repeater {
            model: block && block.parameters

            Loader {
                readonly property Parameter parameter: modelData

                Layout.alignment: Qt.AlignVCenter

                Component { id: booleanView; BooleanView { parameter: parent.parameter } }
                Component { id: choiceView; ChoiceView { parameter: parent.parameter } }
                Component { id: constantView; ConstantView { parameter: parent.parameter } }
                Component { id: expressionView; ExpressionView { parameter: parent.parameter } }
                Component { id: numberView; NumberView { parameter: parent.parameter } }
                Component { id: stringView; StringView { parameter: parent.parameter } }

                Component {
                    id: fallbackParameter

                    ConstantView {
                        text: "(unsupported: type=%1; value=%2)".arg(parent.parameter.type).arg(parent.parameter.value)
                    }
                }

                sourceComponent: {
                    if (parameter.expression)
                        return expressionView;

                    switch (parameter.type) {
                    case Parameter.BooleanType: return booleanView;
                    case Parameter.ChoiceType: return choiceView;
                    case Parameter.ConstantType: return constantView;
                    case Parameter.NumberType: return numberView;
                    case Parameter.StringType: return stringView;
                    }

                    return fallbackParameter;
                }
            }
        }
    }

    Repeater {
        id: scriptRepeater

        model: block && block.scripts

        ColumnLayout {
            readonly property Script script: modelData
            readonly property real labelPadding: (scriptLabel.visible ? scriptLabel.height + spacing : 0)

            Layout.leftMargin: 15
            Layout.bottomMargin: 10
            Layout.minimumHeight: 10 + labelPadding
            Layout.fillWidth: true

            spacing: -1

            ConstantView {
                id: scriptLabel
                Layout.topMargin: -(script.blocks.length ? 5 : 10)
                Layout.bottomMargin: (script.blocks.length ? 5 : 10)
                text: block.scriptNames && block.scriptNames[model.index - 1] || ""
                visible: text
            }

            Repeater {
                model: script.blocks

                BlockView {
                    Layout.fillWidth: true
                    block: modelData
                }
            }
        }
    }
}