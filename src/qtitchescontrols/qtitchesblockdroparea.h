#ifndef QTITCHESBLOCKDROPAREA_H
#define QTITCHESBLOCKDROPAREA_H

#include "qtitchesblock.h"

#include <QQuickItem>

namespace QtItches {
namespace Controls {

class BlockDropArea : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int acceptedDropActions READ acceptedDropActions WRITE setAcceptedDropActions NOTIFY acceptedDropActionsChanged FINAL)
    Q_PROPERTY(int pendingDropAction READ pendingDropAction NOTIFY pendingDropActionChanged FINAL)

public:
    enum DropAction {
        PrependBlock = (1 << 0),
        AppendBlock = (1 << 1),
        ApplyBooleanExpression = (1 << 2),
        ApplyNumberExpression = (1 << 3),
        ApplyStringExpression = (1 << 4),
    };

    Q_FLAG(DropAction)
    Q_DECLARE_FLAGS(DropActions, DropAction)

    explicit BlockDropArea(QQuickItem *parent = {});

    void setAcceptedDropActions(DropActions acceptedDropActions);
    DropActions acceptedDropActions() const;

    DropAction pendingDropAction() const;
    QByteArray typeInfo() const;

public slots:
    virtual QVariantMap createMimeData(const QJsonObject &typeInfo) const;

signals:
    void acceptedDropActionsChanged(int acceptedDropActions);
    void pendingDropActionChanged(int pendingDropAction);
    void typeInfoDropped(DropAction dropAction, const QByteArray &typeInfo);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void setAcceptedDropActions(int acceptedDropActions) { setAcceptedDropActions(static_cast<DropActions>(acceptedDropActions)); }

private:
    void cancelDrop();
    bool eventViolatesAction(QDropEvent *event, DropAction action) const;

    DropActions m_acceptedDropActions;
    DropAction m_pendingDropAction = {};
    bool m_pendingDropSuspended = false;
    QByteArray m_typeInfo;
};

} // namespace Controls
} // namespace QtItches

Q_DECLARE_OPERATORS_FOR_FLAGS(QtItches::Controls::BlockDropArea::DropActions)

#endif // QTITCHESBLOCKDROPAREA_H
