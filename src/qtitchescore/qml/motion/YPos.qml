import QtItches.Core 1.0

Expression {
    category: Expression.MotionCategory
    shape: Expression.ReporterShape
    type: Parameter.NumberType
    value: actor && actor.y || 0

    ConstantParameter { string: qsTr("y") }
}
