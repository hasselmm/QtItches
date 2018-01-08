#ifndef QTITCHESPROJECT_H
#define QTITCHESPROJECT_H

#include <QQmlListProperty>
#include <QQmlParserStatus>

namespace QtItches {
namespace Core {

class ScriptContext;
class Sprite;
class Stage;

class Project : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QQmlListProperty<QtItches::Core::ScriptContext> contextes READ contextes CONSTANT FINAL)
    Q_PROPERTY(QQmlListProperty<QtItches::Core::Sprite> sprites READ sprites CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Stage *stage READ stage CONSTANT FINAL)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged FINAL)
    Q_CLASSINFO("DefaultProperty", "sprites")

public:
    Project(QObject *parent = {});

    QQmlListProperty<ScriptContext> contextes();
    QQmlListProperty<Sprite> sprites();
    Stage *stage() const;

    void setName(const QString &name);
    QString name() const;

    bool running() const;

    // QQmlParserStatus interface
    void classBegin() override;
    void componentComplete() override;

public slots:
    void stop();

signals:
    void flagClicked(QObject *source);
    void nameChanged(const QString &name);
    void runningChanged(bool running);

private:
    void updateRunningState();

    bool m_running = false;
    QList<Sprite *> m_sprites;
    Stage *const m_stage;
    QString m_name;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESPROJECT_H
