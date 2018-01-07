#ifndef QTITCHESSPRITE_H
#define QTITCHESSPRITE_H

#include "qtitchesscriptcontext.h"

#include <QPointF>
#include <QUrl>

namespace QtItches {
namespace Core {

class Sprite : public ScriptContext
{
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "scripts")

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY positionChanged FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY positionChanged FINAL)
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY positionChanged FINAL)
    Q_PROPERTY(qreal direction READ direction WRITE setDirection NOTIFY directionChanged FINAL)
    Q_PROPERTY(QList<QUrl> costumes READ costumes WRITE setCostumes NOTIFY costumesChanged FINAL)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString saying READ saying NOTIFY said FINAL)
    Q_PROPERTY(QString thinking READ thinking NOTIFY thought FINAL)

public:
    using ScriptContext::ScriptContext;

    void setX(qreal x);
    qreal x() const;

    void setY(qreal y);
    qreal y() const;

    void setPosition(const QPointF &position);
    QPointF position() const;

    void setDirection(qreal direction);
    qreal direction() const;

    void setCostumes(const QList<QUrl> &costumes);
    QList<QUrl> costumes() const;

    void setName(const QString &name);
    QString name() const;

    QString saying() const;
    QString thinking() const;

public slots:
    void say(const QString &text);
    void think(const QString &text);
    void goForward(int steps);

signals:
    void clicked(QObject *source);

    void positionChanged(const QPointF &point);
    void directionChanged(qreal direction);
    void costumesChanged(const QList<QUrl> &costumes);
    void nameChanged(const QString &name);
    void said(const QString &text);
    void thought(const QString &text);

private:
    QString m_name;
    QString m_saying;
    QString m_thinking;
    QPointF m_position = {0, 0};
    qreal m_direction = 90;
    QList<QUrl> m_costumes;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESSPRITE_H
