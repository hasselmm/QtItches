#include "qtitchessprite.h"
#include "qtitchesblock.h"
#include "qtitchesexpression.h"
#include "qtitchesblocklibrary.h"
#include "qtitchesparameter.h"
#include "qtitchesscript.h"
#include "qtitchesstage.h"

#include <QDirIterator>
#include <QQmlComponent>
#include <QQmlExtensionPlugin>

class qtitchescoreplugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri)
    {
        Q_INIT_RESOURCE(qtitchescoreplugin);
        Q_ASSERT(uri == QLatin1String("QtItches.Core"));
        using namespace QtItches::Core;

        qmlRegisterType<And>(uri, 1, 0, "And");
        qmlRegisterType<BinaryExpression>(uri, 1, 0, "BinaryExpression");
        qmlRegisterType<BlockLibrary>(uri, 1, 0, "Library");
        qmlRegisterType<Block>(uri, 1, 0, "Block");
        qmlRegisterType<BooleanParameter>(uri, 1, 0, "BooleanParameter");
        qmlRegisterType<ChoiceParameter>(uri, 1, 0, "ChoiceParameter");
        qmlRegisterType<ConstantParameter>(uri, 1, 0, "ConstantParameter");
        qmlRegisterType<Divide>(uri, 1, 0, "Divide");
        qmlRegisterType<Equals>(uri, 1, 0, "Equals");
        qmlRegisterType<Expression>(uri, 1, 0, "Expression");
        qmlRegisterType<GreaterThan>(uri, 1, 0, "GreaterThan");
        qmlRegisterType<LessThan>(uri, 1, 0, "LessThan");
        qmlRegisterType<Minus>(uri, 1, 0, "Minus");
        qmlRegisterType<Multiply>(uri, 1, 0, "Multiply");
        qmlRegisterType<Not>(uri, 1, 0, "Not");
        qmlRegisterType<NumberParameter>(uri, 1, 0, "NumberParameter");
        qmlRegisterType<Or>(uri, 1, 0, "Or");
        qmlRegisterType<Plus>(uri, 1, 0, "Plus");
        qmlRegisterType<Script>(uri, 1, 0, "Script");
        qmlRegisterType<Sprite>(uri, 1, 0, "Sprite");
        qmlRegisterType<Stage>(uri, 1, 0, "Stage");
        qmlRegisterType<StringParameter>(uri, 1, 0, "StringParameter");
        qmlRegisterType<UnaryExpression>(uri, 1, 0, "UnaryExpression");

        const auto abstractBaseClass = tr("This is an abstract base class");
        qmlRegisterUncreatableType<Parameter>(uri, 1, 0, "Parameter", abstractBaseClass);
        qmlRegisterUncreatableType<ScriptContext>(uri, 1, 0, "ScriptContext", abstractBaseClass);

        for (QDirIterator it{":/imports/QtItches/Core", {"*.qml"},
             QDir::Files, QDirIterator::Subdirectories}; it.hasNext(); ) {
            const QUrl url{"qrc" + it.next()};
            const auto qmlName = it.fileInfo().baseName().toUtf8();
            qmlRegisterType(url, uri, 1, 0, qmlName.constData());
        }
    }
};

#include "qtitchescoreplugin.moc"
