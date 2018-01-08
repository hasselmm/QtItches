#include "qtitchesexpression.h"

namespace QtItches {
namespace Core {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Expression::setType(Parameter::Type type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

void Expression::setValue(const QVariant &value)
{
    if (m_value.userType() == value.userType() && m_value == value)
        return;

    m_value = value;
    emit valueChanged(m_value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BinaryExpression::BinaryExpression(Parameter::Type type, const QString &name, QObject *parent)
    : Expression{parent}
{
    const auto center = new ConstantParameter{name, this};
    resetParameters({nullptr, center, nullptr});

    connect(center, &ConstantParameter::stringChanged, this, &BinaryExpression::nameChanged);
    connect(this, &BinaryExpression::typeChanged, this, &BinaryExpression::onTypeChanged);

    setCategory(OperatorsCategory);
    setType(type);
}

void BinaryExpression::onTypeChanged(int type)
{
    setShape(type == Parameter::BooleanType ? BooleanShape : ReporterShape);

    const auto left = Parameter::create(static_cast<Parameter::Type>(type), this);
    const auto right = Parameter::create(static_cast<Parameter::Type>(type), this);

    if (left)
        connect(left, &Parameter::valueChanged, this, &BinaryExpression::leftChanged);
    if (right)
        connect(right, &Parameter::valueChanged, this, &BinaryExpression::rightChanged);

    resetParameters({left, nameParameter(), right});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UnaryExpression::UnaryExpression(Parameter::Type type, const QString &name, QObject *parent)
    : Expression{parent}
{
    const auto left = new ConstantParameter{name, this};
    resetParameters({left, nullptr});

    connect(left, &ConstantParameter::stringChanged, this, &UnaryExpression::nameChanged);
    connect(this, &UnaryExpression::typeChanged, this, &UnaryExpression::onTypeChanged);

    setCategory(OperatorsCategory);
    setType(type);
}

void UnaryExpression::onTypeChanged(int type)
{
    setShape(type == Parameter::BooleanType ? BooleanShape : ReporterShape);

    const auto right = Parameter::create(static_cast<Parameter::Type>(type), this);
    connect(right, &Parameter::valueChanged, this, &UnaryExpression::argumentChanged);
    resetParameters({nameParameter(), right});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Plus::Plus(QObject *parent)
    : BinaryExpression{Parameter::NumberType, QT_TR_NOOP("+"), parent}
{
    connect(this, &Plus::leftChanged, this, &Plus::evaluate);
    connect(this, &Plus::rightChanged, this, &Plus::evaluate);
}

void Plus::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() +
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Minus::Minus(QObject *parent)
    : BinaryExpression{Parameter::NumberType, QT_TR_NOOP("-"), parent}
{
    connect(this, &Minus::leftChanged, this, &Minus::evaluate);
    connect(this, &Minus::rightChanged, this, &Minus::evaluate);
}

void Minus::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() -
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Multiply::Multiply(QObject *parent)
    : BinaryExpression{Parameter::NumberType, QT_TR_NOOP("*"), parent}
{
    connect(this, &Multiply::leftChanged, this, &Multiply::evaluate);
    connect(this, &Multiply::rightChanged, this, &Multiply::evaluate);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Multiply::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() *
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Divide::Divide(QObject *parent)
    : BinaryExpression{Parameter::NumberType, QT_TR_NOOP("/"), parent}
{
    connect(this, &Divide::leftChanged, this, &Divide::evaluate);
    connect(this, &Divide::rightChanged, this, &Divide::evaluate);
}

void Divide::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() /
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LessThan::LessThan(QObject *parent)
    : BinaryExpression{Parameter::NumberType, QT_TR_NOOP("<"), parent}
{
    connect(this, &LessThan::leftChanged, this, &LessThan::evaluate);
    connect(this, &LessThan::rightChanged, this, &LessThan::evaluate);
}

void LessThan::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() <
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GreaterThan::GreaterThan(QObject *parent)
    : BinaryExpression{Parameter::NumberType, QT_TR_NOOP(">"), parent}
{
    connect(this, &GreaterThan::leftChanged, this, &GreaterThan::evaluate);
    connect(this, &GreaterThan::rightChanged, this, &GreaterThan::evaluate);
}

void GreaterThan::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() >
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Equals::Equals(QObject *parent)
    : BinaryExpression{Parameter::StringType, QT_TR_NOOP("="), parent}
{
    connect(this, &Equals::leftChanged, this, &Equals::evaluate);
    connect(this, &Equals::rightChanged, this, &Equals::evaluate);
}

void Equals::evaluate()
{
    setValue(left() == right());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

And::And(QObject *parent)
    : BinaryExpression{Parameter::BooleanType, QT_TR_NOOP("and"), parent}
{
    connect(this, &And::leftChanged, this, &And::evaluate);
    connect(this, &And::rightChanged, this, &And::evaluate);
}

void And::evaluate()
{
    setValue(leftParameter<BooleanParameter>()->boolean() &&
             rightParameter<BooleanParameter>()->boolean());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Or::Or(QObject *parent)
    : BinaryExpression{Parameter::BooleanType, QT_TR_NOOP("or"), parent}
{
    connect(this, &Or::leftChanged, this, &Or::evaluate);
    connect(this, &Or::rightChanged, this, &Or::evaluate);
}

void Or::evaluate()
{
    setValue(leftParameter<BooleanParameter>()->boolean() ||
             rightParameter<BooleanParameter>()->boolean());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Not::Not(QObject *parent)
    : UnaryExpression{Parameter::BooleanType, QT_TR_NOOP("not"), parent}
{
    connect(this, &Not::argumentChanged, this, &Not::evaluate);
}

void Not::evaluate()
{
    setValue(!argumentParameter<BooleanParameter>()->boolean());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Core
} // namespace QtItches
