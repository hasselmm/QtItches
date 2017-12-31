#include "qtitchesstage.h"

namespace QtItches {

class Stage::Private
{
public:
    QList<Actor *> m_actors;
    QString m_name;
};

Stage::Stage(QObject *parent)
    : QObject{parent}
    , d{new Private}
{}

Stage::~Stage()
{
    delete d;
}

QQmlListProperty<Actor> Stage::actors()
{
    return {this, d->m_actors};
}

void Stage::setName(const QString &name)
{
    if (d->m_name == name)
        return;

    d->m_name = name;
    emit nameChanged(d->m_name);
}

QString Stage::name() const
{
    return d->m_name;
}

} // namespace QtItches
