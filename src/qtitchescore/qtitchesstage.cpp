#include "qtitchesstage.h"

#include "qtitchessprite.h"

namespace QtItches {
namespace Core {

void Stage::setBackdrops(const QList<QUrl> &backdrops)
{
    if (m_backdrops == backdrops)
        return;

    m_backdrops = backdrops;
    emit backdropsChanged(m_backdrops);
}

QList<QUrl> Stage::backdrops() const
{
    return m_backdrops;
}

} // namespace Core
} // namespace QtItches
