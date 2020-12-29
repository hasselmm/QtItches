#include "qtitchesscript.h"

#include "qtitchessprite.h"
#include "qtitchesblock.h"
#include "qtitchesstage.h"

#include <QLoggingCategory>
#include <QTimer>

namespace QtItches {
namespace Core {

namespace {
Q_LOGGING_CATEGORY(lcScript, "qtitches.script")
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Script::Private
{
public:
    explicit Private(Script *script)
        : m_script{script} {}

    void acquire(Block *block);
    Block *currentBlock() const;
    void onBlockFinished(Block *block);
    void runBlock(int index);

    Script *const m_script;
    int m_currentIndex = -1;
    QList<Block *> m_blocks;
    bool m_stopped = false;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Script::Private::acquire(Block *block)
{
    block->setParent(m_script);

    connect(block, &Block::finished, m_script, [this, block] {
        onBlockFinished(block);
    });
}

Block *Script::Private::currentBlock() const
{
    if (m_currentIndex >= 0)
        return m_blocks.at(m_currentIndex);

    return {};
}

void Script::Private::onBlockFinished(Block *block)
{
    if (block != currentBlock() && m_currentIndex >= 0) {
        qCWarning(lcScript, "Finished signal received for block %d which is not the current block", m_blocks.indexOf(block));
        return;
    }

    runBlock(m_stopped ? -1 : m_currentIndex + 1);
}

void Script::Private::runBlock(int index)
{
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Script::Script(QObject *parent)
    : QObject{parent}
    , d{new Private{this}}
{}

Script::~Script()
{
    delete d;
}

ScriptContext *Script::context() const
{
    if (const auto s = parentScript())
        return s->context();

    return dynamic_cast<ScriptContext *>(parent());
}

Project *Script::project() const
{
    if (const auto c = context())
        return c->project();

    return {};
}

Sprite *Script::sprite() const
{
    return dynamic_cast<Sprite *>(context());
}

Script *Script::parentScript() const
{
    if (const auto b = dynamic_cast<Block *>(parent()))
        return b->script();

    return {};
}

Stage *Script::stage() const
{
    return dynamic_cast<Stage *>(context());
}

QQmlListProperty<Block> Script::blocks()
{
    return {this, &d->m_blocks};
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
    for (auto block: qAsConst(d->m_blocks))
        d->acquire(block);
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
    d->m_stopped = true;

    if (const auto block = currentBlock())
        block->metaObject()->invokeMethod(block, "stop");
}

void Script::insertBefore(Block *before, Block *block)
{
    const auto index = d->m_blocks.indexOf(before);
    if (index >= 0)
        insert(index, block);
}

void Script::insertAfter(Block *after, Block *block)
{
    const auto index = d->m_blocks.indexOf(after);
    if (index >= 0)
        insert(index + 1, block);
}

void Script::insert(int index, Block *block)
{
    if (index >= 0 && index < d->m_blocks.size()) {
        d->acquire(block);
        d->m_blocks.insert(index, block);
        emit blocksChanged(); // FIXME: replace with QALM for better performance
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Core
} // namespace QtItches
