#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStaticPlugin>

static void initResources()
{
    Q_INIT_RESOURCE(qtitchescontrolsplugin);
    Q_INIT_RESOURCE(qtitchescoreplugin);
}

Q_IMPORT_PLUGIN(qtitchescontrolsplugin)
Q_IMPORT_PLUGIN(qtitchescoreplugin)

namespace QtItches {

class DemoApplication : public QGuiApplication
{
public:
    using QGuiApplication::QGuiApplication;

    int run()
    {
        initResources();

        QQmlApplicationEngine qml;
        qml.addImportPath("qrc:/imports");
        qml.load(QUrl{"qrc:/qml/main.qml"});

        if (qml.rootObjects().isEmpty())
            return EXIT_FAILURE;

        return exec();
    }
};

} // namespace QtItches

int main(int argc, char *argv[])
{
    return QtItches::DemoApplication{argc, argv}.run();
}
