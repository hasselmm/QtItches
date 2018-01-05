#include "qtitchesscriptcontext.h"

#include "qtitchesproject.h"
#include "qtitchesscript.h"

namespace QtItches {
namespace Core {

Project *ScriptContext::project() const
{
    return dynamic_cast<Project *>(parent());
}

void ScriptContext::stopAllButThis(Script *script)
{
    for (const auto s: m_scripts) {
        if (s != script)
            s->stop();
    }
}

void ScriptContext::stop()
{
    stopAllButThis({});
}

QQmlListProperty<Script> ScriptContext::scripts()
{
    return {this, m_scripts};
}

} // namespace Core
} // namespace QtItches
