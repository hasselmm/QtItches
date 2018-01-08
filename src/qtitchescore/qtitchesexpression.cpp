#include "qtitchesexpression.h"

namespace QtItches {
namespace Core {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Expression::setParameterType(Parameter::Type parameterType)
{
    if (m_parameterType == parameterType)
        return;

    m_parameterType = parameterType;
    emit parameterTypeChanged(m_parameterType);
}

void Expression::setResultType(Parameter::Type resultType)
{
    if (m_resultType == resultType)
        return;

    m_resultType = resultType;
    emit resultTypeChanged(m_resultType);
}

void Expression::setValue(const QVariant &value)
{
    if (m_value.userType() == value.userType() && m_value == value)
        return;

    m_value = value;
    emit valueChanged(m_value);
}

Block::TypeCategory Expression::typeCategory() const
{
    switch (resultType()) {
    case Parameter::BooleanType:
        return BooleanExpressionTypeCategory;

    case Parameter::ChoiceType:
    case Parameter::NumberType:
        return NumberExpressionTypeCategory;

    case Parameter::ConstantType:
    case Parameter::StringType:
        return StringExpressionTypeCategory;

    case Parameter::InvalidType:
        break;
    }

    return {};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BinaryExpression::BinaryExpression(Parameter::Type resultType, Parameter::Type parameterType,
                                   const QString &name, QObject *parent)
    : Expression{parent}
{
    const auto center = new ConstantParameter{name, this};
    resetParameters({nullptr, center, nullptr});

    connect(center, &ConstantParameter::stringChanged, this, &BinaryExpression::nameChanged);
    connect(this, &BinaryExpression::parameterTypeChanged, this, &BinaryExpression::onParameterTypeChanged);
    connect(this, &BinaryExpression::resultTypeChanged, this, &BinaryExpression::onResultTypeChanged);

    setCategory(OperatorsCategory);
    setParameterType(parameterType);
    setResultType(resultType);
}

void BinaryExpression::onParameterTypeChanged(int parameterType)
{
    const auto left = Parameter::create(static_cast<Parameter::Type>(parameterType), this);
    const auto right = Parameter::create(static_cast<Parameter::Type>(parameterType), this);

    if (left)
        connect(left, &Parameter::valueChanged, this, &BinaryExpression::leftChanged);
    if (right)
        connect(right, &Parameter::valueChanged, this, &BinaryExpression::rightChanged);

    resetParameters({left, nameParameter(), right});
}

void BinaryExpression::onResultTypeChanged(int resultType)
{
    setShape(resultType == Parameter::BooleanType ? BooleanShape : ReporterShape);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UnaryExpression::UnaryExpression(Parameter::Type resultType, Parameter::Type parameterType,
                                 const QString &name, QObject *parent)
    : Expression{parent}
{
    const auto left = new ConstantParameter{name, this};
    resetParameters({left, nullptr});

    connect(left, &ConstantParameter::stringChanged, this, &UnaryExpression::nameChanged);
    connect(this, &UnaryExpression::parameterTypeChanged, this, &UnaryExpression::onParameterTypeChanged);
    connect(this, &UnaryExpression::resultTypeChanged, this, &UnaryExpression::onResultTypeChanged);

    setCategory(OperatorsCategory);
    setParameterType(parameterType);
    setResultType(resultType);
}

void UnaryExpression::onParameterTypeChanged(int parameterType)
{
    const auto right = Parameter::create(static_cast<Parameter::Type>(parameterType), this);
    connect(right, &Parameter::valueChanged, this, &UnaryExpression::argumentChanged);
    resetParameters({nameParameter(), right});
}

void UnaryExpression::onResultTypeChanged(int resultType)
{
    setShape(resultType == Parameter::BooleanType ? BooleanShape : ReporterShape);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Plus::Plus(QObject *parent)
    : BinaryExpression{Parameter::NumberType, Parameter::NumberType, QT_TR_NOOP("+"), parent}
{
    connect(this, &Plus::leftChanged, this, &Plus::evaluate);
    connect(this, &Plus::rightChanged, this, &Plus::evaluate);
    evaluate();
}

void Plus::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() +
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Minus::Minus(QObject *parent)
    : BinaryExpression{Parameter::NumberType, Parameter::NumberType, QT_TR_NOOP("-"), parent}
{
    connect(this, &Minus::leftChanged, this, &Minus::evaluate);
    connect(this, &Minus::rightChanged, this, &Minus::evaluate);
    evaluate();
}

void Minus::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() -
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Multiply::Multiply(QObject *parent)
    : BinaryExpression{Parameter::NumberType, Parameter::NumberType, QT_TR_NOOP("*"), parent}
{
    connect(this, &Multiply::leftChanged, this, &Multiply::evaluate);
    connect(this, &Multiply::rightChanged, this, &Multiply::evaluate);
    evaluate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Multiply::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() *
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Divide::Divide(QObject *parent)
    : BinaryExpression{Parameter::NumberType, Parameter::NumberType, QT_TR_NOOP("/"), parent}
{
    connect(this, &Divide::leftChanged, this, &Divide::evaluate);
    connect(this, &Divide::rightChanged, this, &Divide::evaluate);
    evaluate();
}

void Divide::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() /
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LessThan::LessThan(QObject *parent)
    : BinaryExpression{Parameter::BooleanType, Parameter::NumberType, QT_TR_NOOP("<"), parent}
{
    connect(this, &LessThan::leftChanged, this, &LessThan::evaluate);
    connect(this, &LessThan::rightChanged, this, &LessThan::evaluate);
    evaluate();
}

void LessThan::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() <
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GreaterThan::GreaterThan(QObject *parent)
    : BinaryExpression{Parameter::BooleanType, Parameter::NumberType, QT_TR_NOOP(">"), parent}
{
    connect(this, &GreaterThan::leftChanged, this, &GreaterThan::evaluate);
    connect(this, &GreaterThan::rightChanged, this, &GreaterThan::evaluate);
    evaluate();
}

void GreaterThan::evaluate()
{
    setValue(leftParameter<NumberParameter>()->number() >
             rightParameter<NumberParameter>()->number());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Equals::Equals(QObject *parent)
    : BinaryExpression{Parameter::BooleanType, Parameter::StringType, QT_TR_NOOP("="), parent}
{
    connect(this, &Equals::leftChanged, this, &Equals::evaluate);
    connect(this, &Equals::rightChanged, this, &Equals::evaluate);
    evaluate();
}

void Equals::evaluate()
{
    setValue(left() == right());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

And::And(QObject *parent)
    : BinaryExpression{Parameter::BooleanType, Parameter::BooleanType, QT_TR_NOOP("and"), parent}
{
    connect(this, &And::leftChanged, this, &And::evaluate);
    connect(this, &And::rightChanged, this, &And::evaluate);
    evaluate();
}

void And::evaluate()
{
    setValue(leftParameter<BooleanParameter>()->boolean() &&
             rightParameter<BooleanParameter>()->boolean());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Or::Or(QObject *parent)
    : BinaryExpression{Parameter::BooleanType, Parameter::BooleanType, QT_TR_NOOP("or"), parent}
{
    connect(this, &Or::leftChanged, this, &Or::evaluate);
    connect(this, &Or::rightChanged, this, &Or::evaluate);
    evaluate();
}

void Or::evaluate()
{
    setValue(leftParameter<BooleanParameter>()->boolean() ||
             rightParameter<BooleanParameter>()->boolean());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Not::Not(QObject *parent)
    : UnaryExpression{Parameter::BooleanType, Parameter::BooleanType, QT_TR_NOOP("not"), parent}
{
    connect(this, &Not::argumentChanged, this, &Not::evaluate);
    evaluate();
}

void Not::evaluate()
{
    setValue(!argumentParameter<BooleanParameter>()->boolean());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Core
} // namespace QtItches
