import QtItches.Core 1.0

Expression {
    category: Expression.MotionCategory
    shape: Expression.ReporterShape
    type: Parameter.NumberType
    value: actor && actor.x || 0

    ConstantParameter { string: qsTr("x position") }
}
