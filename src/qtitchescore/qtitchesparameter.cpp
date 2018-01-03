#include "qtitchesparameter.h"

#include "qtitchesexpression.h"

#include <QQmlInfo>

namespace QtItches {
namespace Core {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Parameter::Parameter(QObject *parent)
    : QObject{parent}
{}

Parameter *Parameter::create(Type type, QObject *parent)
{
    switch(type) {
    case BooleanType:
        return new BooleanParameter{parent};
    case ChoiceType:
        return new ChoiceParameter{parent};
    case ConstantType:
        return new ConstantParameter{parent};
    case NumberType:
        return new NumberParameter{parent};
    case StringType:
        return new StringParameter{parent};
    case InvalidType:
        break;
    }

    return {};
}

void Parameter::setExpression(Expression *expression)
{
    if (type() == InvalidType)
        qWarning("TODO: derrive parameter type from initital expressions");

    setValue(qVariantFromValue(expression));
}

Expression *Parameter::expression() const
{
    return m_value.value<Expression *>();
}

void Parameter::setValue(const QVariant &value)
{
    if (m_value.userType() == value.userType() && m_value == value)
        return;

    if (!acceptableValue(value)) {
        qmlWarning(this) << "Ignoring unsupported value of type " << value.typeName();
        return;
    }

    if (const auto e = expression())
        e->disconnect(this);

    m_value = value;

    if (const auto e = expression())
        connect(e, &Expression::valueChanged, this, &Parameter::valueChanged);

    emit valueChanged(value);
}

QVariant Parameter::value() const
{
    if (const auto e = expression())
        return e->value();

    return m_value;
}

bool Parameter::acceptableValue(const QVariant &value) const
{
    if (value.canConvert(qMetaTypeId<Expression *>())) {
        qWarning("TODO: properly validate expressions");
        return true;
    }

    switch (type()) {
    case BooleanType:
        return value.canConvert(QVariant::Bool);
    case ChoiceType:
        return value.canConvert(QVariant::Int);
    case ConstantType:
        return value.canConvert(QVariant::String);
    case NumberType:
        return value.canConvert(QVariant::Double);
    case StringType:
        return value.canConvert(QVariant::String);
    case InvalidType:
        break;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BooleanParameter::BooleanParameter(QObject *parent)
    : Parameter{parent}
{
    connect(this, &Parameter::valueChanged, [this](const auto &value) {
        emit this->booleanChanged(value.toBool());
    });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ChoiceParameter::ChoiceParameter(QObject *parent)
    : Parameter{parent}
{
    connect(this, &Parameter::valueChanged, [this](const auto &value) {
        emit this->currentIndexChanged(value.toInt());
    });
}

void ChoiceParameter::setModel(const QStringList &model)
{
    if (m_model == model)
        return;

    m_model = model;
    emit modelChanged(m_model);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ConstantParameter::ConstantParameter(QObject *parent)
    : Parameter{parent}
{
    connect(this, &Parameter::valueChanged, [this](const auto &value) {
        emit this->stringChanged(value.toString());
    });
}

ConstantParameter::ConstantParameter(const QString &string, QObject *parent)
    : ConstantParameter{parent}
{
    setString(string);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NumberParameter::NumberParameter(QObject *parent)
    : Parameter{parent}
{
    connect(this, &Parameter::valueChanged, [this](const auto &value) {
        emit this->numberChanged(value.toDouble());
    });
}

void NumberParameter::setDecimals(int decimals)
{
    if (m_decimals == decimals)
        return;

    m_decimals = decimals;
    emit decimalsChanged(m_decimals);
}

void NumberParameter::setLowestNumber(double lowestNumber)
{
    if (qFuzzyCompare(m_lowestNumber, lowestNumber))
        return;

    m_lowestNumber = lowestNumber;
    emit lowestNumberChanged(m_lowestNumber);
}

void NumberParameter::setHighestNumber(double highestNumber)
{
    if (qFuzzyCompare(m_highestNumber, highestNumber))
        return;

    m_highestNumber = highestNumber;
    emit higestNumberChanged(m_highestNumber);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StringParameter::StringParameter(QObject *parent)
    : Parameter{parent}
{
    connect(this, &Parameter::valueChanged, [this](const auto &value) {
        emit this->stringChanged(value.toString());
    });
}

void StringParameter::setMaximumLength(int maximumLength)
{
    if (m_maximumLength == maximumLength)
        return;

    m_maximumLength = maximumLength;
    emit maximumLengthChanged(m_maximumLength);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Core
} // namespace QtItches
