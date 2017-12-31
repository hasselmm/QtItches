#ifndef QTITCHESACTOR_H
#define QTITCHESACTOR_H

#include <QQmlListProperty>
#include <QUrl>

namespace QtItches {

class Script;
class Stage;

class Actor : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "scripts")

    Q_PROPERTY(QList<QUrl> costumes READ costumes WRITE setCostumes NOTIFY costumesChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString saying READ saying NOTIFY said FINAL)
    Q_PROPERTY(QString thinking READ thinking NOTIFY thought FINAL)

    Q_PROPERTY(QQmlListProperty<QtItches::Script> scripts READ scripts CONSTANT FINAL)
    Q_PROPERTY(QtItches::Stage *stage READ stage CONSTANT FINAL)


public:
    explicit Actor(QObject *parent = {});
    ~Actor();

    void setCostumes(const QList<QUrl> &costumes);
    QList<QUrl> costumes() const;

    void setName(const QString &name);
    QString name() const;

    QString saying() const;
    QString thinking() const;

    QQmlListProperty<Script> scripts();
    Stage *stage() const;

public slots:
    void say(const QString &text);
    void think(const QString &text);

signals:
    void clicked(QObject *source);
    void costumesChanged(const QList<QUrl> &costumes);
    void nameChanged(const QString &name);
    void said(const QString &text);
    void thought(const QString &text);

private:
    class Private;
    Private *const d;
};

} // namespace QtItches

#endif // QTITCHESACTOR_H
