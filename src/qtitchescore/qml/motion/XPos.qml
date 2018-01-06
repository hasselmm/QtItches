import QtItches.Core 1.0

SpriteExpression {
    category: Expression.MotionCategory
    shape: Expression.ReporterShape
    type: Parameter.NumberType
    value: sprite && sprite.x || 0

    ConstantParameter { string: qsTr("x position") }
}
