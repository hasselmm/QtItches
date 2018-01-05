import QtItches.Core 1.0

Expression {
    category: Expression.MotionCategory
    shape: Expression.ReporterShape
    type: Parameter.NumberType
    value: sprite && sprite.direction || 0

    ConstantParameter { string: qsTr("direction") }
}
