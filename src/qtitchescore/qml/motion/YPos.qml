import QtItches.Core 1.0

SpriteExpression {
    category: Expression.MotionCategory
    shape: Expression.ReporterShape
    type: Parameter.NumberType
    value: sprite && sprite.y || 0

    ConstantParameter { string: qsTr("y  position") }
}
