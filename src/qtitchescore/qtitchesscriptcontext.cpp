#include "qtitchesscriptcontext.h"

#include "qtitchesproject.h"
#include "qtitchesscript.h"

namespace QtItches {
namespace Core {

Project *ScriptContext::project() const
{
    return dynamic_cast<Project *>(parent());
}

bool ScriptContext::running() const
{
    return m_running;
}

void ScriptContext::classBegin()
{}

void ScriptContext::componentComplete()
{
    for (auto s: qAsConst(m_scripts))
        connect(s, &Script::runningChanged, this, &ScriptContext::updateRunningState);
}

void ScriptContext::stopAllButThis(Script *script)
{
    for (const auto s: qAsConst(m_scripts)) {
        if (s != script)
            s->stop();
    }
}

void ScriptContext::stop()
{
    stopAllButThis({});
}

void ScriptContext::updateRunningState()
{
    const auto running = [this] {
        for (auto s: qAsConst(m_scripts)) {
            if (s->running())
                return true;
        }

        return false;
    }();

    if (m_running != running) {
        m_running = running;
        emit runningChanged(m_running);
    }
}

QQmlListProperty<Script> ScriptContext::scripts()
{
    return {this, &m_scripts};
}

} // namespace Core
} // namespace QtItches
