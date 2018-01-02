#include "qtitchesactor.h"

#include "qtitchesstage.h"

#include <QLoggingCategory>

#include <cmath>

namespace QtItches {
namespace Core {

namespace {
Q_LOGGING_CATEGORY(lcActor, "qtitches.actor")
}

class Actor::Private
{
public:
    QList<QUrl> m_costumes;
    QString m_name;
    QString m_saying;
    QString m_thinking;
    QPointF m_position = {0, 0};
    double m_direction = 90;

    QList<Script *> m_scripts;
};

Actor::Actor(QObject *parent)
    : QObject{parent}
    , d{new Private}
{}

Actor::~Actor()
{
    delete d;
}

void Actor::setX(double x)
{
    setPosition({x, y()});
}

double Actor::x() const
{
    return d->m_position.x();
}

void Actor::setY(double y)
{
    setPosition({x(), y});
}

double Actor::y() const
{
    return d->m_position.y();
}

void Actor::setPosition(const QPointF &position)
{
    if (d->m_position == position)
        return;

    d->m_position = position;
    emit positionChanged(d->m_position);
}

QPointF Actor::position() const
{
    return d->m_position;
}

void Actor::setDirection(double direction)
{
    if (d->m_direction == direction)
        return;

    while (direction > 180)
        direction -= 360;
    while (direction < -180)
        direction += 360;

    d->m_direction = direction;
    emit directionChanged(d->m_direction);
}

double Actor::direction() const
{
    return d->m_direction;
}

void Actor::setCostumes(const QList<QUrl> &costumes)
{
    if (d->m_costumes == costumes)
        return;

    d->m_costumes = costumes;
    emit costumesChanged(d->m_costumes);
}

QList<QUrl> Actor::costumes() const
{
    return d->m_costumes;
}

void Actor::setName(const QString &name)
{
    if (d->m_name == name)
        return;

    d->m_name = name;
    emit nameChanged(d->m_name);
}

QString Actor::name() const
{
    return d->m_name;
}

QString Actor::saying() const
{
    return d->m_saying;
}

QString Actor::thinking() const
{
    return d->m_thinking;
}

Stage *Actor::stage() const
{
    return dynamic_cast<Stage *>(parent());
}

void Actor::say(const QString &text)
{
    if (!text.isEmpty())
        qCInfo(lcActor, "%ls says: `%ls'", qUtf16Printable(name()), qUtf16Printable(text));

    d->m_saying = text;
    emit said(d->m_saying); // really always emit
}

void Actor::think(const QString &text)
{
    if (!text.isEmpty())
        qCInfo(lcActor, "%ls thinks: `%ls'", qUtf16Printable(name()), qUtf16Printable(text));

    d->m_thinking = text;
    emit thought(d->m_thinking); // really always emit
}

void Actor::goForward(int steps)
{
    if (steps > 0) {
        // MIT Scratch has a very special idea of basic trigonometry
        const auto dx = steps * cos(M_PI * (90 - direction()) / 180);
        const auto dy = steps * sin(M_PI * (90 - direction()) / 180);
        d->m_position += {dx, dy};
        emit positionChanged(d->m_position);
    }
}

QQmlListProperty<Script> Actor::scripts()
{
    return {this, d->m_scripts};
}

} // namespace Core
} // namespace QtItches
