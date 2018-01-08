#ifndef QTITCHESEXPRESSION_H
#define QTITCHESEXPRESSION_H

#include "qtitchesblock.h"
#include "qtitchesparameter.h"

#define QTITCHES_DECLARE_BINARY_EXPRESSION(Name) \
    class Name : public BinaryExpression { \
        Q_OBJECT \
    public: explicit Name(QObject *parent = {}); \
    private: void evaluate(); \
    }

#define QTITCHES_DECLARE_UNARY_EXPRESSION(Name) \
    class Name : public UnaryExpression { \
        Q_OBJECT \
    public: explicit Name(QObject *parent = {}); \
    private: void evaluate(); \
    }

namespace QtItches {
namespace Core {

class Expression : public Block
{
    Q_OBJECT
    Q_PROPERTY(int parameterType READ parameterType WRITE setParameterType NOTIFY parameterTypeChanged FINAL)
    Q_PROPERTY(int resultType READ resultType WRITE setResultType NOTIFY resultTypeChanged FINAL)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged FINAL)

public:
    explicit Expression(QObject *parent = {});

    void setParameterType(Parameter::Type parameterType);
    Parameter::Type parameterType() const { return m_parameterType; }

    void setResultType(Parameter::Type resultType);
    Parameter::Type resultType() const { return m_resultType; }

    void setValue(const QVariant &value);
    QVariant value() const { return m_value; }

    TypeCategory typeCategory() const override;

signals:
    void parameterTypeChanged(int parameterType);
    void resultTypeChanged(int resultType);
    void valueChanged(const QVariant &value);

private:
    void setParameterType(int parameterType) { setParameterType(static_cast<Parameter::Type>(parameterType)); }
    void setResultType(int resultType) { setResultType(static_cast<Parameter::Type>(resultType)); }

    Parameter::Type m_parameterType = Parameter::InvalidType;
    Parameter::Type m_resultType = Parameter::InvalidType;
    QVariant m_value;
};

class BinaryExpression : public Expression
{
    Q_OBJECT

    Q_PROPERTY(QVariant left READ left WRITE setLeft NOTIFY leftChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QVariant right READ right WRITE setRight NOTIFY rightChanged FINAL)

protected:
    explicit BinaryExpression(QObject *parent = {})
        : BinaryExpression{Parameter::InvalidType, Parameter::InvalidType, {}, parent} {}
    explicit BinaryExpression(Parameter::Type resultType, Parameter::Type parameterType,
                              const QString &name, QObject *parent = {});

public:
    void setLeft(const QVariant &left) { leftParameter()->setValue(left); }
    QVariant left() const { return leftParameter()->value(); }

    void setName(const QString &name) { nameParameter()->setString(name); }
    QString name() const { return nameParameter()->string(); }

    void setRight(const QVariant &right) { rightParameter()->setValue(right); }
    QVariant right() const { return rightParameter()->value(); }

signals:
    void leftChanged(const QVariant &left);
    void nameChanged(const QString &name);
    void rightChanged(const QVariant &right);

protected:
    template<class T = Parameter> T *leftParameter() const { return parameter<T>(0); }
    ConstantParameter *nameParameter() const { return parameter<ConstantParameter>(1); }
    template<class T = Parameter> T *rightParameter() const { return parameter<T>(2); }

private:
    void onParameterTypeChanged(int parameterType);
    void onResultTypeChanged(int resultType);
};

class UnaryExpression : public Expression
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QVariant argument READ argument WRITE setArgument NOTIFY argumentChanged FINAL)

protected:
    explicit UnaryExpression(QObject *parent = {})
        : UnaryExpression{Parameter::InvalidType, Parameter::InvalidType, {}, parent} {}
    explicit UnaryExpression(Parameter::Type resultType, Parameter::Type parameterType,
                             const QString &name, QObject *parent = {});

public:
    void setName(const QString &name) { nameParameter()->setString(name); }
    QString name() const { return nameParameter()->string(); }

    void setArgument(const QVariant &argument) { argumentParameter()->setValue(argument); }
    QVariant argument() const { return argumentParameter()->value(); }

signals:
    void nameChanged(const QString &name);
    void argumentChanged(const QVariant &argument);

protected:
    ConstantParameter *nameParameter() const { return parameter<ConstantParameter>(0); }
    template<class T = Parameter> T *argumentParameter() const { return parameter<T>(1); }

private:
    void onParameterTypeChanged(int parameterType);
    void onResultTypeChanged(int resultType);
};

QTITCHES_DECLARE_BINARY_EXPRESSION(Plus);
QTITCHES_DECLARE_BINARY_EXPRESSION(Minus);
QTITCHES_DECLARE_BINARY_EXPRESSION(Multiply);
QTITCHES_DECLARE_BINARY_EXPRESSION(Divide);

QTITCHES_DECLARE_BINARY_EXPRESSION(And);
QTITCHES_DECLARE_BINARY_EXPRESSION(Equals);
QTITCHES_DECLARE_BINARY_EXPRESSION(GreaterThan);
QTITCHES_DECLARE_BINARY_EXPRESSION(LessThan);
QTITCHES_DECLARE_BINARY_EXPRESSION(Or);

QTITCHES_DECLARE_UNARY_EXPRESSION(Not);

} // namespace Core
} // namespace QtItches

#endif // QTITCHESEXPRESSION_H
