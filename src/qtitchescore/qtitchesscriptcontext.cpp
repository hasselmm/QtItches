#include "qtitchesscriptcontext.h"

#include "qtitchesscript.h"
#include "qtitchesstage.h"

namespace QtItches {
namespace Core {

Stage *ScriptContext::stage() const
{
    return dynamic_cast<Stage *>(parent());
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
