#include "qtitchesexpression.h"

#include <QSignalSpy>
#include <QTest>

#define QTITCHES_COMPARE(actual, expected, line) do { \
    if (!QTest::qCompare(actual, expected, #actual, #expected, __FILE__, line))\
        return;\
} while (false)

namespace QTest {

template<> inline char *toString(const QList<QVariantList> &list)
{
    QString buffer;
    QDebug(&buffer) << list;
    return qstrdup(buffer.toLocal8Bit().constData());
}

template<> inline char *toString(const QSignalSpy &spy)
{
    return toString<QList<QVariantList>>(spy);
}

}

namespace QtItches {
namespace Core {

struct BinaryExpressionSpy
{
    BinaryExpressionSpy(BinaryExpression *expr)
        : left{expr, &BinaryExpression::leftChanged}
        , right{expr, &BinaryExpression::rightChanged}
        , value{expr, &BinaryExpression::valueChanged}
    {}

    QSignalSpy left;
    QSignalSpy right;
    QSignalSpy value;
};

struct UnaryExpressionSpy
{
    UnaryExpressionSpy(UnaryExpression *expr)
        : argument{expr, &UnaryExpression::argumentChanged}
        , value{expr, &BinaryExpression::valueChanged}
    {}

    QSignalSpy argument;
    QSignalSpy value;
};

struct ExpressionState
{
    ExpressionState(QVariantList &&argumentChanges, QVariantList &&valueChanges)
        : argumentChanges{toSignalList(std::move(argumentChanges))}
        , valueChanges{toSignalList(std::move(valueChanges))}
    {}

    ExpressionState(QVariantList &&leftChanges, QVariantList &&rightChanges, QVariantList &&valueChanges)
        : leftChanges{toSignalList(std::move(leftChanges))}
        , rightChanges{toSignalList(std::move(rightChanges))}
        , valueChanges{toSignalList(std::move(valueChanges))}
    {}

    QList<QVariantList> argumentChanges;
    QList<QVariantList> leftChanges;
    QList<QVariantList> rightChanges;
    QList<QVariantList> valueChanges;

    QVariant argument() const { return lastValue(argumentChanges); }
    QVariant left() const { return lastValue(leftChanges); }
    QVariant right() const { return lastValue(rightChanges); }
    QVariant value() const { return lastValue(valueChanges); }

private:
    static QVariant lastValue(const QList<QVariantList> &list) { return !list.isEmpty() ? list.last().first() : QVariant{}; }
    static QVariantList toVariantList(const QVariant &value) { return {value}; }

    static QList<QVariantList> toSignalList(QVariantList &&list)
    {
        QList<QVariantList> result;
        result.reserve(list.size());
        std::transform(list.begin(), list.end(), std::back_inserter(result), toVariantList);
        return result;
    }
};

template<typename T> class VerifyExpression
{
public:
    VerifyExpression(const BinaryExpression &actualExpression,
                     const BinaryExpressionSpy &actualChanges,
                     const ExpressionState &expected, int line)
    {
        QTITCHES_COMPARE(actualExpression.left().typeName(), expected.left().typeName(), line);
        QTITCHES_COMPARE(actualExpression.left().value<T>(), expected.left().value<T>(), line);
        QTITCHES_COMPARE(actualChanges.left, expected.leftChanges, line);

        QTITCHES_COMPARE(actualExpression.right().typeName(), expected.right().typeName(), line);
        QTITCHES_COMPARE(actualExpression.right().value<T>(), expected.right().value<T>(), line);
        QTITCHES_COMPARE(actualChanges.right, expected.rightChanges, line);

        QTITCHES_COMPARE(actualExpression.value().typeName(), expected.value().typeName(), line);
        QTITCHES_COMPARE(actualExpression.value().value<T>(), expected.value().value<T>(), line);
        QTITCHES_COMPARE(actualChanges.value, expected.valueChanges, line);
    }

    VerifyExpression(const UnaryExpression &actualExpression,
                     const UnaryExpressionSpy &actualChanges,
                     const ExpressionState &expected, int line)
    {
        QTITCHES_COMPARE(actualExpression.argument().typeName(), expected.argument().typeName(), line);
        QTITCHES_COMPARE(actualExpression.argument().value<T>(), expected.argument().value<T>(), line);
        QTITCHES_COMPARE(actualChanges.argument, expected.argumentChanges, line);

        QTITCHES_COMPARE(actualExpression.value().typeName(), expected.value().typeName(), line);
        QTITCHES_COMPARE(actualExpression.value().value<T>(), expected.value().value<T>(), line);
        QTITCHES_COMPARE(actualChanges.value, expected.valueChanges, line);
    }

    explicit operator bool() const { return !QTest::currentTestFailed(); }
};

#define VERIFY_EXPRESSION(type, expr, spy, ...) do { \
    if (!VerifyExpression<type>(expr, spy, {__VA_ARGS__}, __LINE__)) \
        return; \
} while (false)

class ExpressionsTest : public QObject
{
    Q_OBJECT

private slots:
    void testPlus()
    {
        Plus expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(double, expr, spy, {}, {}, {});

        expr.setLeft(1);
        VERIFY_EXPRESSION(double, expr, spy, {1}, {}, {1.0});

        expr.setRight(2.3);
        VERIFY_EXPRESSION(double, expr, spy, {1}, {2.3}, {1.0, 3.3});
    }

    void testMinus()
    {
        Minus expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(double, expr, spy, {}, {}, {});

        expr.setLeft(1);
        VERIFY_EXPRESSION(double, expr, spy, {1}, {}, {1.0});

        expr.setRight(2.3);
        VERIFY_EXPRESSION(double, expr, spy, {1}, {2.3}, {1.0, -1.3});
    }

    void testMultiply()
    {
        Multiply expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(double, expr, spy, {}, {}, {});

        expr.setLeft(2);
        VERIFY_EXPRESSION(double, expr, spy, {2}, {}, {0.0});

        expr.setRight(2.3);
        VERIFY_EXPRESSION(double, expr, spy, {2}, {2.3}, {0.0, 4.6});
    }

    void testDivide()
    {
        Divide expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(double, expr, spy, {}, {}, {});

        expr.setRight(2);
        VERIFY_EXPRESSION(double, expr, spy, {}, {2}, {0.0});

        expr.setLeft(1.5);
        VERIFY_EXPRESSION(double, expr, spy, {1.5}, {2}, {0.0, 0.75});
    }

    void testAnd()
    {
        And expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(bool, expr, spy, {}, {}, {});

        expr.setLeft(true);
        VERIFY_EXPRESSION(bool, expr, spy, {true}, {}, {false});

        expr.setRight(2);
        VERIFY_EXPRESSION(bool, expr, spy, {true}, {2}, {false, true});

        expr.setRight(0);
        VERIFY_EXPRESSION(bool, expr, spy, {true}, {2, 0}, {false, true, false});

        expr.setLeft(false);
        VERIFY_EXPRESSION(bool, expr, spy, {true, false}, {2, 0}, {false, true, false});
    }

    void testOr()
    {
        Or expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(bool, expr, spy, {}, {}, {});

        expr.setLeft(true);
        VERIFY_EXPRESSION(bool, expr, spy, {true}, {}, {true});

        expr.setRight(2);
        VERIFY_EXPRESSION(bool, expr, spy, {true}, {2}, {true});

        expr.setLeft(false);
        VERIFY_EXPRESSION(bool, expr, spy, {true, false}, {2}, {true});

        expr.setRight(0);
        VERIFY_EXPRESSION(bool, expr, spy, {true, false}, {2, 0}, {true, false});
    }

    void testEquals()
    {
        Equals expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(bool, expr, spy, {}, {}, {});

        expr.setLeft(1);
        VERIFY_EXPRESSION(bool, expr, spy, {1}, {}, {false});

        expr.setRight(2.0);
        VERIFY_EXPRESSION(bool, expr, spy, {1}, {2.0}, {false});

        expr.setRight(1.0);
        VERIFY_EXPRESSION(bool, expr, spy, {1}, {2.0, 1.0}, {false, true});

        expr.setLeft(true);
        VERIFY_EXPRESSION(bool, expr, spy, {1, true}, {2.0, 1.0}, {false, true});

        expr.setRight("foo");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true}, {2.0, 1.0, "foo"}, {false, true});

        expr.setLeft("foo");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true, "foo"}, {2.0, 1.0, "foo"}, {false, true});

        expr.setLeft("bar");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true, "foo", "bar"}, {2.0, 1.0, "foo"}, {false, true, false});
    }

    void testLessThan()
    {
        LessThan expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(bool, expr, spy, {}, {}, {});

        expr.setLeft(1);
        VERIFY_EXPRESSION(bool, expr, spy, {1}, {}, {false});

        expr.setRight(2.0);
        VERIFY_EXPRESSION(bool, expr, spy, {1}, {2.0}, {false, true});

        expr.setLeft(true);
        VERIFY_EXPRESSION(bool, expr, spy, {1, true}, {2.0}, {false, true});

        expr.setRight("foo");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true}, {2.0, "foo"}, {false, true, false});

        expr.setLeft("foo");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true, "foo"}, {2.0, "foo"}, {false, true, false});

        expr.setLeft("bar");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true, "foo", "bar"}, {2.0, "foo"}, {false, true, false});
    }

    void testGreaterThan()
    {
        GreaterThan expr; BinaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(bool, expr, spy, {}, {}, {});

        expr.setLeft(1);
        VERIFY_EXPRESSION(bool, expr, spy, {1}, {}, {true});

        expr.setRight(0.5);
        VERIFY_EXPRESSION(bool, expr, spy, {1}, {0.5}, {true});

        expr.setLeft(true);
        VERIFY_EXPRESSION(bool, expr, spy, {1, true}, {0.5}, {true});

        expr.setRight("foo");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true}, {0.5, "foo"}, {true});

        expr.setLeft("foo");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true, "foo"}, {0.5, "foo"}, {true, false});

        expr.setLeft("bar");
        VERIFY_EXPRESSION(bool, expr, spy, {1, true, "foo", "bar"}, {0.5, "foo"}, {true, false});
    }

    void testNot()
    {
        Not expr; UnaryExpressionSpy spy{&expr};
        VERIFY_EXPRESSION(bool, expr, spy, {}, {}, {});

        expr.setArgument(false);
        VERIFY_EXPRESSION(bool, expr, spy, {false}, {true});

        expr.setArgument(true);
        VERIFY_EXPRESSION(bool, expr, spy, {false, true}, {true, false});
    }
};

} // namespace Core
} // namespace QtItches

QTEST_GUILESS_MAIN(QtItches::Core::ExpressionsTest)

#include "tst_expressions.moc"
