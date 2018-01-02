#ifndef QTITCHESCATEGORYMODEL_H
#define QTITCHESCATEGORYMODEL_H

#include "qtitchesutils.h"

#include <QAbstractListModel>

namespace QtItches {
namespace Controls {

class CategoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRole {
        NameRole = Qt::DisplayRole,
        ColorRole = Qt::DecorationRole,
        CategoryRole = Qt::UserRole,
    };

    QTITCHES_DATAROLE(DataRole)
    explicit CategoryModel(QObject *parent = {});
    ~CategoryModel();

    static QColor categoryColor(int category);
    static QString categoryName(int category);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    class Private;
    Private *const d;
};

} // namespace Controls
} // namespace QtItches

#endif // QTITCHESCATEGORYMODEL_H
