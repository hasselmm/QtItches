#include "qtitchesblockdroparea.h"

#include "qtitchesblocklibrary.h"
#include "qtitchesmetaenumiterator.h"

#include <QJsonDocument>
#include <QMimeData>

namespace QtItches {
namespace Controls {

namespace {

const auto s_mimeTypeBlockType = QStringLiteral("application/vnd.qtitches.blocktype");
const auto s_mimeTypeBooleanExpression = QStringLiteral("application/vnd.qtitches.boolean+expression+blocktype");
const auto s_mimeTypeNumberExpression = QStringLiteral("application/vnd.qtitches.number+expression+blocktype");
const auto s_mimeTypeStringExpression = QStringLiteral("application/vnd.qtitches.string+expression+blocktype");

QString mimeTypeForTypeCategory(Core::Block::TypeCategory typeCategory)
{
    switch (typeCategory) {
    case Core::Block::BlockTypeCategory:
        return s_mimeTypeBlockType;

    case Core::Block::BooleanExpressionTypeCategory:
        return s_mimeTypeBooleanExpression;

    case Core::Block::NumberExpressionTypeCategory:
        return s_mimeTypeNumberExpression;

    case Core::Block::StringExpressionTypeCategory:
        return s_mimeTypeStringExpression;
    }

    return {};
}

QString mimeTypeForAction(BlockDropArea::DropAction dropAction)
{
    switch (dropAction) {
    case BlockDropArea::PrependBlock:
    case BlockDropArea::AppendBlock:
        return s_mimeTypeBlockType;

    case BlockDropArea::ApplyBooleanExpression:
        return s_mimeTypeBooleanExpression;

    case BlockDropArea::ApplyNumberExpression:
        return s_mimeTypeNumberExpression;

    case BlockDropArea::ApplyStringExpression:
        return s_mimeTypeStringExpression;
    }

    return {};
}

} // namespace

BlockDropArea::BlockDropArea(QQuickItem *parent)
    : QQuickItem{parent}
{
    setFlag(ItemAcceptsDrops);
}

void BlockDropArea::setAcceptedDropActions(DropActions acceptedDropActions)
{
    if (m_acceptedDropActions == acceptedDropActions)
        return;

    m_acceptedDropActions = acceptedDropActions;
    emit acceptedDropActionsChanged(m_acceptedDropActions);
}

BlockDropArea::DropActions BlockDropArea::acceptedDropActions() const
{
    return m_acceptedDropActions;
}

BlockDropArea::DropAction BlockDropArea::pendingDropAction() const
{
    return m_pendingDropSuspended ? DropAction{} : m_pendingDropAction;
}

QByteArray BlockDropArea::typeInfo() const
{
    return m_typeInfo;
}

QVariantMap BlockDropArea::createMimeData(const QJsonObject &typeInfo) const
{
    const auto typeCategory = Core::BlockLibrary::typeCategory(typeInfo);
    const auto mimeType = mimeTypeForTypeCategory(typeCategory);

    if (!mimeType.isEmpty())
        return {{mimeType, QJsonDocument{typeInfo}.toJson(QJsonDocument::Compact)}};

    return {};
}

void BlockDropArea::dragEnterEvent(QDragEnterEvent *event)
{
    const auto mimeData = event->mimeData();
    for (const auto &member: QMetaEnum::fromType<DropAction>()) {
        const auto action = member.value<DropAction>();

        if (eventViolatesAction(event, action))
            continue;

        if ((m_acceptedDropActions & action) == action) {
            m_typeInfo = mimeData->data(mimeTypeForAction(action));

            if (!m_typeInfo.isEmpty()) {
                event->accept();
                m_pendingDropAction = action;
                emit pendingDropActionChanged(m_pendingDropAction);
                return;
            }
        }
    }

    cancelDrop();
    QQuickItem::dragEnterEvent(event);
}

void BlockDropArea::dragMoveEvent(QDragMoveEvent *event)
{
    if (m_pendingDropAction) {
        const auto suspendRequired = eventViolatesAction(event, m_pendingDropAction);
        if (m_pendingDropSuspended != suspendRequired) {
            m_pendingDropSuspended = suspendRequired;
            emit pendingDropActionChanged(pendingDropAction());
        }
    }

    QQuickItem::dragMoveEvent(event);
}

void BlockDropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    if (m_pendingDropAction) {
        cancelDrop();
    } else {
        QQuickItem::dragLeaveEvent(event);
    }
}

void BlockDropArea::dropEvent(QDropEvent *event)
{
    if (m_pendingDropAction) {
        event->accept();
        emit typeInfoDropped(m_pendingDropAction, m_typeInfo);
        cancelDrop();
    } else {
        QQuickItem::dropEvent(event);
    }
}

void BlockDropArea::cancelDrop()
{
    m_typeInfo.clear();
    m_pendingDropAction = {};
    emit pendingDropActionChanged(m_pendingDropAction);
}

bool BlockDropArea::eventViolatesAction(QDropEvent *event, BlockDropArea::DropAction action) const
{
    if (action == PrependBlock && event->pos().y() >= height()/2)
        return true;
    if (action == AppendBlock && event->pos().y() < height()/2)
        return true;

    return false;
}

} // namespace Controls
} // namespace QtItches
