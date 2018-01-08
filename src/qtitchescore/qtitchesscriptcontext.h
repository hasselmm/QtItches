#ifndef QTITCHESSCRIPTCONTEXT_H
#define QTITCHESSCRIPTCONTEXT_H

#include <QQmlListProperty>
#include <QQmlParserStatus>

namespace QtItches {
namespace Core {

class Project;
class Script;

class ScriptContext : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_CLASSINFO("DefaultProperty", "scripts")
    Q_PROPERTY(QQmlListProperty<QtItches::Core::Script> scripts READ scripts CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Project *project READ project CONSTANT FINAL)

public:
    using QObject::QObject;

    QQmlListProperty<Script> scripts();
    Project *project() const;

    bool running() const;

    // QQmlParserStatus interface
    void classBegin() override;
    void componentComplete() override;

public slots:
    void stopAllButThis(QtItches::Core::Script *script);
    void stop();

signals:
    void runningChanged(bool running);

private:
    void updateRunningState();

    bool m_running = false;
    QList<Script *> m_scripts;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESSCRIPTCONTEXT_H
