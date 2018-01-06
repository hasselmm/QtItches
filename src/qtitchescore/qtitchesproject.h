#ifndef QTITCHESPROJECT_H
#define QTITCHESPROJECT_H

#include <QQmlListProperty>

namespace QtItches {
namespace Core {

class ScriptContext;
class Sprite;
class Stage;

class Project : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QQmlListProperty<QtItches::Core::ScriptContext> contextes READ contextes CONSTANT FINAL)
    Q_PROPERTY(QQmlListProperty<QtItches::Core::Sprite> sprites READ sprites CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Stage *stage READ stage CONSTANT FINAL)
    Q_CLASSINFO("DefaultProperty", "sprites")

public:
    Project(QObject *parent = {});

    QQmlListProperty<ScriptContext> contextes();
    QQmlListProperty<Sprite> sprites();
    Stage *stage() const;

    void setName(const QString &name);
    QString name() const;

public:
    void stop();

signals:
    void flagClicked(QObject *source);
    void nameChanged(const QString &name);

private:
    QList<Sprite *> m_sprites;
    Stage *const m_stage;
    QString m_name;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESPROJECT_H
