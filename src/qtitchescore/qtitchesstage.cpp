#include "qtitchesstage.h"

#include "qtitchessprite.h"

namespace QtItches {
namespace Core {

class Stage::Private
{
public:
    QList<Sprite *> m_sprites;
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

QQmlListProperty<Sprite> Stage::sprites()
{
    return {this, d->m_sprites};
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

void Stage::stop()
{
    for (const auto s: d->m_sprites)
        s->stop();
}

} // namespace Core
} // namespace QtItches
