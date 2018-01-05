#ifndef QTITCHESSCRIPTCONTEXT_H
#define QTITCHESSCRIPTCONTEXT_H

#include <QQmlListProperty>

namespace QtItches {
namespace Core {

class Project;
class Script;

class ScriptContext : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "scripts")
    Q_PROPERTY(QQmlListProperty<QtItches::Core::Script> scripts READ scripts CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Project *project READ project CONSTANT FINAL)

public:
    using QObject::QObject;

    QQmlListProperty<Script> scripts();
    Project *project() const;

public slots:
    void stopAllButThis(QtItches::Core::Script *script);
    void stop();

private:
    QList<Script *> m_scripts;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESSCRIPTCONTEXT_H
