#include "qtitchesparameter.h"

#include "qtitchesexpression.h"
#include "qtitchesutils.h"

#include <QQmlInfo>

namespace QtItches {
namespace Core {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Parameter::Parameter(QObject *parent)
    : Parameter{{}, parent}
{}

Parameter::Parameter(const QVariant &initialValue, QObject *parent)
    : QObject{parent}
    , m_value{initialValue}
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

    setValue(QVariant::fromValue(expression));
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
        if (const auto e = value.value<Expression *>()) {
            qmlWarning(this) << "Ignoring expression with unsupported result type " << valueToKey(e->resultType())
                             << " and a value of " << e->value();
        } else {
            qmlWarning(this) << "Ignoring value of unsupported type " << value.typeName();
        }

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

QString Parameter::toPlainText()
{
    const auto delimiters = Parameter::delimiters(type());

    QString plainText;

    if (!delimiters.first.isNull())
        plainText += delimiters.first;

    if (const auto e = expression())
        plainText += e->toPlainText();
    else
        plainText += m_value.toString();

    if (!delimiters.second.isNull())
        plainText += delimiters.second;

    return plainText;
}

bool Parameter::acceptableValue(const QVariant &value) const
{
    if (value.isNull())
        return true;

    if (const auto expression = value.value<Expression *>())
        return acceptableValue(expression->value());

    switch (type()) {
    case Parameter::BooleanType:
        return value.canConvert(QVariant::Bool);
    case Parameter::ChoiceType:
        return value.canConvert(QVariant::Int);
    case Parameter::ConstantType:
        return value.canConvert(QVariant::String);
    case Parameter::NumberType:
        return value.canConvert(QVariant::Double);
    case Parameter::StringType:
        return value.canConvert(QVariant::String);
    case Parameter::InvalidType:
        break;
    }

    return false;
}

Q_DECL_RELAXED_CONSTEXPR std::pair<QChar, QChar> Parameter::delimiters(Parameter::Type type)
{
    switch (type) {
    case BooleanType:
        return {'<', '>'};
    case ChoiceType:
    case NumberType:
        return {'(', ')'};
    case StringType:
        return {'[', ']'};

    case ConstantType:
    case InvalidType:
        break;
    }

    return {};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BooleanParameter::BooleanParameter(QObject *parent)
    : Parameter{false, parent}
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
    : Parameter{0.0, parent}
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
