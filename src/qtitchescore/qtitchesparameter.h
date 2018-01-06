#ifndef QTITCHESPARAMETER_H
#define QTITCHESPARAMETER_H

#include <QObject>
#include <QVariant>

namespace QtItches {
namespace Core {

class Expression;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Parameter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int type READ type CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Expression *expression READ expression WRITE setExpression NOTIFY valueChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged FINAL)

public:
    enum Type {
        InvalidType,
        BooleanType,
        ChoiceType,
        ConstantType,
        NumberType,
        StringType,
    };

    Q_ENUM(Type)

protected:
    explicit Parameter(QObject *parent = {});
    explicit Parameter(const QVariant &initialValue, QObject *parent = {});

public:
    static Parameter *create(Type type, QObject *parent = {});
    virtual Type type() const = 0;

    void setExpression(Expression *expression);
    Expression *expression() const;

    void setValue(const QVariant &value);
    QVariant value() const;

public slots:
    QString toPlainText();

signals:
    void valueChanged(const QVariant &value);

private:
    bool acceptableValue(const QVariant &value) const;
    static Q_DECL_RELAXED_CONSTEXPR std::pair<QChar, QChar> delimiters(Type type);

    QVariant m_value;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BooleanParameter : public Parameter
{
    Q_OBJECT
    Q_PROPERTY(bool boolean READ boolean WRITE setBoolean NOTIFY booleanChanged FINAL)

public:
    explicit BooleanParameter(QObject *parent = {});

    Type type() const override { return BooleanType; }

    void setBoolean(bool boolean) { setValue(boolean); }
    bool boolean() const { return value().toBool(); }

signals:
    void booleanChanged(bool boolean);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ChoiceParameter : public Parameter
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged FINAL)
    Q_PROPERTY(QStringList model READ model WRITE setModel NOTIFY modelChanged FINAL)

public:
    explicit ChoiceParameter(QObject *parent = {});

    Type type() const override { return ChoiceType; }

    void setCurrentIndex(int currentIndex) { setValue(currentIndex); }
    int currentIndex() const { return value().toInt(); }

    void setModel(const QStringList &model);
    QStringList model() const { return m_model; }

signals:
    void currentIndexChanged(int currentIndex);
    void modelChanged(const QStringList &model);

private:
    QStringList m_model;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ConstantParameter : public Parameter
{
    Q_OBJECT
    Q_PROPERTY(QString string READ string WRITE setString NOTIFY stringChanged FINAL)

public:
    explicit ConstantParameter(QObject *parent = {});
    explicit ConstantParameter(const QString &string, QObject *parent = {});

    Type type() const override { return ConstantType; }

    void setString(const QString &string) { setValue(string); }
    QString string() const { return value().toString(); }

signals:
    void stringChanged(const QString &string);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NumberParameter : public Parameter
{
    Q_OBJECT
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged FINAL)
    Q_PROPERTY(double lowestNumber READ lowestNumber WRITE setLowestNumber NOTIFY lowestNumberChanged FINAL)
    Q_PROPERTY(double highestNumber READ highestNumber WRITE setHighestNumber NOTIFY higestNumberChanged FINAL)
    Q_PROPERTY(double number READ number WRITE setNumber NOTIFY numberChanged FINAL)

public:
    explicit NumberParameter(QObject *parent = {});

    Type type() const override { return NumberType; }

    void setDecimals(int decimals);
    int decimals() const { return m_decimals; }

    void setLowestNumber(double lowestNumber);
    double lowestNumber() const { return m_lowestNumber; }

    void setHighestNumber(double highestNumber);
    double highestNumber() const { return m_highestNumber; }

    void setNumber(double number) { setValue(number); }
    double number() const { return value().toDouble(); }

signals:
    void decimalsChanged(int decimals);
    void higestNumberChanged(double highestNumber);
    void lowestNumberChanged(double lowestNumber);
    void numberChanged(double number);

private:
    int m_decimals = 1000;
    double m_lowestNumber = 0;
    double m_highestNumber = 1000;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StringParameter : public Parameter
{
    Q_OBJECT
    Q_PROPERTY(int maximumLength READ maximumLength WRITE setMaximumLength NOTIFY maximumLengthChanged FINAL)
    Q_PROPERTY(QString string READ string WRITE setString NOTIFY stringChanged FINAL)

public:
    explicit StringParameter(QObject *parent = {});

    Type type() const override { return StringType; }

    void setMaximumLength(int maximumLength);
    int maximumLength() const { return m_maximumLength; }

    void setString(const QString &string) { setValue(string); }
    QString string() const { return value().toString(); }

signals:
    void maximumLengthChanged(int maximumLength);
    void stringChanged(const QString &string);

private:
    int m_maximumLength = 1000;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Core
} // namespace QtItches

#endif // QTITCHESPARAMETER_H
