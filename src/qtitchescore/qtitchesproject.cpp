#include "qtitchesstage.h"

#include "qtitchesproject.h"
#include "qtitchessprite.h"

namespace QtItches {
namespace Core {

Project::Project(QObject *parent)
    : QObject{parent}
    , m_stage{new Stage{this}}
{}

QQmlListProperty<ScriptContext> Project::contextes()
{
    static const auto count = [](auto list) {
        const auto project = static_cast<Project *>(list->object);
        return project->m_sprites.size() + 1;
    };

    static const auto at = [](auto list, int index) -> ScriptContext * {
        const auto project = static_cast<Project *>(list->object);

        if (index-- == 0)
            return project->m_stage;
        if (index >= 0 && index < project->m_sprites.size())
            return project->m_sprites.at(index);

        return {};
    };

    return {this, nullptr, count, at};
}

QQmlListProperty<Sprite> Project::sprites()
{
    return {this, &m_sprites};
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

bool Project::running() const
{
    return m_running;
}

void Project::classBegin()
{}

void Project::componentComplete()
{
    for (auto s: m_sprites)
        connect(s, &ScriptContext::runningChanged, this, &Project::updateRunningState);

    connect(m_stage, &ScriptContext::runningChanged, this, &Project::updateRunningState);
}

void Project::stop()
{
    for (const auto s: m_sprites)
        s->stop();

    m_stage->stop();
}

void Project::updateRunningState()
{
    const auto running = [this] {
        for (auto s: m_sprites) {
            if (s->running())
                return true;
        }

        return m_stage->running();
    }();

    if (m_running != running) {
        m_running = running;
        emit runningChanged(m_running);
    }
}

} // namespace Core
} // namespace QtItches
