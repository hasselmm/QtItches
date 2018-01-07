import QtItches.Core 1.0

SpriteExpression {
    category: Expression.MotionCategory
    shape: Expression.ReporterShape
    resultType: Parameter.NumberType
    value: sprite && sprite.x || 0

    ConstantParameter { string: QT_TR_NOOP("x position") }
}
