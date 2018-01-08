import QtItches.Core 1.0
import QtItches.Controls 1.0

import QtQuick 2.9

Item {
    property Parameter parameter

    implicitWidth: expressionView.implicitWidth
    implicitHeight: expressionView.implicitHeight

    BlockView {
        id: expressionView

        acceptedDropActions: {
            switch (parameter && parameter.type) {
            case Parameter.BooleanType:
                return BlockDropArea.ApplyBooleanExpression;

            case Parameter.NumberType:
                return (BlockDropArea.ApplyNumberExpression |
                        BlockDropArea.ApplyBooleanExpression);

            case Parameter.StringType:
                return (BlockDropArea.ApplyStringExpression |
                        BlockDropArea.ApplyNumberExpression |
                        BlockDropArea.ApplyBooleanExpression);
            }

            return 0;
        }

        block: parameter && parameter.expression
        onTypeInfoDropped: parameter.value = BlockView.createBlock(typeInfo)
    }
}
