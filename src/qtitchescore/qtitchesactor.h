#ifndef QTITCHESACTOR_H
#define QTITCHESACTOR_H

#include <QPointF>
#include <QQmlListProperty>
#include <QUrl>

namespace QtItches {
namespace Core {

class Script;
class Stage;

class Actor : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "scripts")

    Q_PROPERTY(double x READ x WRITE setX NOTIFY positionChanged FINAL)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY positionChanged FINAL)
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY positionChanged FINAL)
    Q_PROPERTY(double direction READ direction WRITE setDirection NOTIFY directionChanged FINAL)
    Q_PROPERTY(QList<QUrl> costumes READ costumes WRITE setCostumes NOTIFY costumesChanged FINAL)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString saying READ saying NOTIFY said FINAL)
    Q_PROPERTY(QString thinking READ thinking NOTIFY thought FINAL)

    Q_PROPERTY(QQmlListProperty<QtItches::Core::Script> scripts READ scripts CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Stage *stage READ stage CONSTANT FINAL)

public:
    explicit Actor(QObject *parent = {});
    ~Actor();

    void setX(double x);
    double x() const;

    void setY(double y);
    double y() const;

    void setPosition(const QPointF &position);
    QPointF position() const;

    void setDirection(double direction);
    double direction() const;

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
    void goForward(int steps);

signals:
    void clicked(QObject *source);

    void positionChanged(const QPointF &point);
    void directionChanged(double direction);
    void costumesChanged(const QList<QUrl> &costumes);
    void nameChanged(const QString &name);
    void said(const QString &text);
    void thought(const QString &text);

private:
    class Private;
    Private *const d;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESACTOR_H
