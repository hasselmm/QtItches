#include "qtitchesscript.h"

#include "qtitchesactor.h"
#include "qtitchesblock.h"

#include <QLoggingCategory>
#include <QTimer>

namespace QtItches {
namespace Core {

namespace {
Q_LOGGING_CATEGORY(lcScript, "qtitches.script")
}

class Script::Private
{
public:
    explicit Private(Script *script)
        : m_script{script}
    {}

    Block *currentBlock() const
    {
        if (m_currentIndex >= 0)
            return m_blocks.at(m_currentIndex);

        return {};
    }

    void onBlockFinished(Block *block) {
        if (block != currentBlock() && m_currentIndex >= 0) {
            qCWarning(lcScript, "Finished signal received for block %d which is not the current block", m_blocks.indexOf(block));
            return;
        }

        runBlock(m_stopped ? -1 : m_currentIndex + 1);
    }

    void runBlock(int index) {
        m_currentIndex = (index >= 0 && index < m_blocks.size() ? index : -1);
        emit m_script->currentBlockChanged(currentBlock());

        if (const auto block = currentBlock()) {
            if (m_currentIndex == 0)
                emit m_script->runningChanged(true);

            block->metaObject()->invokeMethod(block, "run");
        } else {
            emit m_script->runningChanged(false);
            emit m_script->finished();
        }
    }

    Script *const m_script;
    int m_currentIndex = -1;
    QList<Block *> m_blocks;
    bool m_stopped = false;
};

Script::Script(QObject *parent)
    : QObject{parent}
    , d{new Private{this}}
{}

Script::~Script()
{
    delete d;
}

Actor *Script::actor() const
{
    if (const auto s = scope())
        return s->actor();

    return dynamic_cast<Actor *>(parent());
}

Script *Script::scope() const
{
    if (const auto b = dynamic_cast<Block *>(parent()))
        return b->script();

    return {};
}

Stage *Script::stage() const
{
    if (const auto a = actor())
        return a->stage();

    return {};
}

QQmlListProperty<Block> Script::blocks()
{
    return {this, d->m_blocks};
}

Block *Script::currentBlock() const
{
    return d->currentBlock();
}

bool Script::running() const
{
    return d->m_currentIndex >= 0;
}

void Script::classBegin()
{
}

void Script::componentComplete()
{
    for (auto block: qAsConst(d->m_blocks)) {
        connect(block, &Block::finished, this, [this, block] {
            d->onBlockFinished(block);
        });
    }
}

bool Script::run()
{
    if (running()) {
        qCWarning(lcScript, "Cannot start already running script");
        return false;
    }

    d->m_stopped = false;
    QTimer::singleShot(0, this, [this] { d->runBlock(0); });
    return true;
}

void Script::stop()
{
    if (const auto block = currentBlock()) {
        block->metaObject()->invokeMethod(block, "stop");
        d->m_stopped = true;
    }
}

} // namespace Core
} // namespace QtItches
