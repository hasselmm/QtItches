#include "qtitchesblockview.h"

#include <QDirIterator>
#include <QQmlComponent>
#include <QQmlExtensionPlugin>

class qtitchescontrolsplugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri)
    {
        Q_INIT_RESOURCE(qtitchescontrolsplugin);
        Q_ASSERT(uri == QLatin1String("QtItches.Controls"));
        using namespace QtItches::Controls;

        qmlRegisterType<BlockView>(uri, 1, 0, "BlockView");

        for (QDirIterator it{":/imports/QtItches/Controls", {"*.qml"},
             QDir::Files, QDirIterator::Subdirectories}; it.hasNext(); ) {
            const QUrl url{"qrc" + it.next()};
            const auto qmlName = it.fileInfo().baseName().toUtf8();
            qmlRegisterType(url, uri, 1, 0, qmlName.constData());
        }
    }
};

#include "qtitchescontrolsplugin.moc"
