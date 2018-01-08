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

BlockDropArea::DropActions actionsForMimeType(const QString &mimeType)
{
    if (mimeType == s_mimeTypeBlockType)
        return BlockDropArea::PrependBlock | BlockDropArea::AppendBlock;
    if (mimeType == s_mimeTypeBooleanExpression)
        return BlockDropArea::ApplyBooleanExpression;
    if (mimeType == s_mimeTypeNumberExpression)
        return BlockDropArea::ApplyNumberExpression;
    if (mimeType == s_mimeTypeStringExpression)
        return BlockDropArea::ApplyStringExpression;

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

BlockDropArea::DropActions BlockDropArea::floatingDropActions() const
{
    return m_floatingDropActions;
}

BlockDropArea::DropAction BlockDropArea::pendingDropAction() const
{
    return m_pendingDropAction;
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
    if (!mimeData)
        return;

    m_typeInfo.clear();
    m_floatingDropActions = {};

    for (const auto &format: mimeData->formats()) {
        if (const auto actions = (actionsForMimeType(format) & m_acceptedDropActions)) {
            if (m_typeInfo.isEmpty())
                m_typeInfo = mimeData->data(format);

            m_floatingDropActions |= actions;
        }
    }

    if ((m_pendingDropAction = findActionForEvent(event)) != 0) {
        event->accept(answerRect(m_pendingDropAction));
        emit pendingDropActionChanged(m_pendingDropAction);
    }

    QQuickItem::dragEnterEvent(event);
}

void BlockDropArea::dragMoveEvent(QDragMoveEvent *event)
{
    const auto action = findActionForEvent(event);

    if (m_pendingDropAction != action) {
        m_pendingDropAction = action;

        if (m_pendingDropAction)
            event->accept(answerRect(m_pendingDropAction));
        else
            event->ignore();

        emit pendingDropActionChanged(m_pendingDropAction);
    }

    QQuickItem::dragMoveEvent(event);
}

void BlockDropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    resetDropActionState();
    QQuickItem::dragLeaveEvent(event);
}

void BlockDropArea::dropEvent(QDropEvent *event)
{
    if (m_pendingDropAction) {
        event->accept();
        emit typeInfoDropped(m_pendingDropAction, m_typeInfo);
    }

    resetDropActionState();
    QQuickItem::dropEvent(event);
}

QRect BlockDropArea::answerRect(BlockDropArea::DropAction action) const
{
    const auto center = height()/2;

    switch(action) {
    case PrependBlock:
        return {0, 0, qRound(width()), qRound(center)};

    case AppendBlock:
        return {0, qRound(height() - center), qRound(width()), qRound(center)};

    case ApplyBooleanExpression:
    case ApplyNumberExpression:
    case ApplyStringExpression:
        break;
    }

    return {};
}

BlockDropArea::DropAction BlockDropArea::findActionForEvent(QDropEvent *event) const
{
    for (const auto &member: QMetaEnum::fromType<DropAction>()) {
        const auto action = member.value<DropAction>();

        if ((m_floatingDropActions & action) == action
                && answerRect(action).contains(event->pos()))
            return action;
    }

    return {};
}

void BlockDropArea::resetDropActionState()
{
    m_typeInfo.clear();
    m_floatingDropActions = {};

    if (std::exchange(m_pendingDropAction, {}))
        emit pendingDropActionChanged(m_pendingDropAction);
}

} // namespace Controls
} // namespace QtItches
