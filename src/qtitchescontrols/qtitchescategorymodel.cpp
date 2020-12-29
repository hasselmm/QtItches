#include "qtitchescategorymodel.h"

#include "qtitchesblock.h"

#include <QColor>
#include <QMetaEnum>

namespace QtItches {
namespace Controls {

namespace {
constexpr auto s_controlCategoryColor = QRgb{0xe1a91a};
constexpr auto s_dataCategoryColor = QRgb{0xee7d16};
constexpr auto s_eventsCategoryColor = QRgb{0xc88330};
constexpr auto s_listsCategoryColor = QRgb{0xca5c2c};
constexpr auto s_looksCategoryColor = QRgb{0x8a55d7};
constexpr auto s_motionCategoryColor = QRgb{0x4a6cd4};
constexpr auto s_operatorsCategoryColor = QRgb{0x5cb712};
constexpr auto s_penCategoryColor = QRgb{0x0e9a6c};
constexpr auto s_sensingCategoryColor = QRgb{0x2ca5e2};
constexpr auto s_soundCategoryColor = QRgb{0xbb42c3};
constexpr auto s_unknownCategoryColor = QRgb{0x4d4b60};
}

class CategoryModel::Private
{
public:
    struct Row
    {
        Row() = default;
        Row(Core::Block::Category category)
            : category{category}
            , color{categoryColor(category)}
            , name{categoryName(category)}
        {}
        Row(int category, QColor &&color, QString &&name)
            : category{category}, color{color}, name{name}
        {}

        int category = Core::Block::UnknownCategory;
        QColor color;
        QString name;
    };

    std::vector<Row> m_rows;
};

CategoryModel::CategoryModel(QObject *parent)
    : QAbstractListModel{parent}
    , d{new Private}
{
    d->m_rows.emplace_back(Core::Block::MotionCategory);
    d->m_rows.emplace_back(Core::Block::LooksCategory);
    d->m_rows.emplace_back(Core::Block::SoundCategory);
    d->m_rows.emplace_back(Core::Block::PenCategory);
    d->m_rows.emplace_back(Core::Block::DataCategory);
    d->m_rows.emplace_back(Core::Block::EventsCategory);
    d->m_rows.emplace_back(Core::Block::ControlCategory);
    d->m_rows.emplace_back(Core::Block::SensingCategory);
    d->m_rows.emplace_back(Core::Block::OperatorsCategory);
    d->m_rows.emplace_back(Core::Block::UnknownCategory);

    Q_ASSERT(d->m_rows.size() == static_cast<size_t>(QMetaEnum::fromType<Core::Block::Category>().keyCount()));
}

CategoryModel::~CategoryModel()
{
    delete d;
}

QColor CategoryModel::categoryColor(int category)
{
    switch (static_cast<Core::Block::Category>(category)) {
    case Core::Block::ControlCategory:
        return s_controlCategoryColor;
    case Core::Block::DataCategory:
        return s_dataCategoryColor;
    case Core::Block::EventsCategory:
        return s_eventsCategoryColor;
    case Core::Block::LooksCategory:
        return s_looksCategoryColor;
    case Core::Block::MotionCategory:
        return s_motionCategoryColor;
    case Core::Block::OperatorsCategory:
        return s_operatorsCategoryColor;
    case Core::Block::PenCategory:
        return s_penCategoryColor;
    case Core::Block::SensingCategory:
        return s_sensingCategoryColor;
    case Core::Block::SoundCategory:
        return s_soundCategoryColor;
    case Core::Block::UnknownCategory:
        break;
    }

    return s_unknownCategoryColor;
}

QString CategoryModel::categoryName(int category)
{
    switch (static_cast<Core::Block::Category>(category)) {
    case Core::Block::ControlCategory:
        return tr("Control");
    case Core::Block::DataCategory:
        return tr("Data");
    case Core::Block::EventsCategory:
        return tr("Events");
    case Core::Block::LooksCategory:
        return tr("Looks");
    case Core::Block::MotionCategory:
        return tr("Motion");
    case Core::Block::OperatorsCategory:
        return tr("Operators");
    case Core::Block::PenCategory:
        return tr("Pen");
    case Core::Block::SensingCategory:
        return tr("Sensing");
    case Core::Block::SoundCategory:
        return tr("Sound");
    case Core::Block::UnknownCategory:
        break;
    }

    return tr("More Blocks");
}

int CategoryModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return static_cast<int>(d->m_rows.size());

    return 0;
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const
{
    if (hasIndex(index.row(), index.column(), index.parent())) {
        switch (static_cast<DataRole>(role)) {
        case CategoryRole:
            return d->m_rows[index.row()].category;
        case ColorRole:
            return d->m_rows[index.row()].color;
        case NameRole:
            return d->m_rows[index.row()].name;
        }
    }

    return {};
}

} // namespace Controls
} // namespace QtItches
