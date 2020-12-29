#ifndef QTITCHESSTAGE_H
#define QTITCHESSTAGE_H

#include "qtitchesscriptcontext.h"

#include <QUrl>

namespace QtItches {
namespace Core {

class Sprite;

class QTITCHES_CORE_EXPORT Stage : public ScriptContext
{
    Q_OBJECT
    Q_PROPERTY(QList<QUrl> backdrops READ backdrops WRITE setBackdrops NOTIFY backdropsChanged FINAL)

public:
    using ScriptContext::ScriptContext;

    void setBackdrops(const QList<QUrl> &backdrops);
    QList<QUrl> backdrops() const;

signals:
    void backdropsChanged(const QList<QUrl> &backdrops);

private:
    QList<QUrl> m_backdrops;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESSTAGE_H
