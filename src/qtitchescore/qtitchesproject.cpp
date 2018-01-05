#include "qtitchesstage.h"

#include "qtitchesproject.h"
#include "qtitchessprite.h"

namespace QtItches {
namespace Core {

Project::Project(QObject *parent)
    : QObject{parent}
    , m_stage{new Stage{this}}
{}

QQmlListProperty<Sprite> Project::sprites()
{
    return {this, m_sprites};
}

Stage *Project::stage() const
{
    return m_stage;
}

void Project::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

QString Project::name() const
{
    return m_name;
}

void Project::stop()
{
    for (const auto s: m_sprites)
        s->stop();

    m_stage->stop();
}

} // namespace Core
} // namespace QtItches
