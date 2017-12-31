#include "qtitchesactor.h"

#include "qtitchesstage.h"

#include <QLoggingCategory>

namespace QtItches {

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
    d->m_saying = text;
    qCInfo(lcActor, "%ls says: `%ls'", qUtf16Printable(name()), qUtf16Printable(text));
    emit said(d->m_saying); // really always emit
}

void Actor::think(const QString &text)
{
    d->m_thinking = text;
    qCInfo(lcActor, "%ls thinks: `%ls'", qUtf16Printable(name()), qUtf16Printable(text));
    emit said(d->m_thinking); // really always emit
}

QQmlListProperty<Script> Actor::scripts()
{
    return {this, d->m_scripts};
}

} // namespace QtItches
