#include "qtitchesblocklibrary.h"

#include "qtitchesblock.h"
#include "qtitchesexpression.h"

#include <private/qhashedstring_p.h>
#include <private/qqmlmetatype_p.h>

#include <QPointer>
#include <QQmlComponent>

#include <memory>

namespace QtItches {
namespace Core {

class BlockLibrary::Private
{
public:
    struct Row
    {
        Row() = default;
        Row(const QQmlType &type, Block *prototype)
            : type{type}, prototype{prototype} {}

        QQmlType type;
        QPointer<Block> prototype;
    };

    std::vector<Row> m_rows;
    QStringList m_modules = {"QtItches.Core"};
};

BlockLibrary::BlockLibrary(QObject *parent)
    : QAbstractListModel(parent)
    , d{new Private}
{}

BlockLibrary::~BlockLibrary()
{
    delete d;
}

void BlockLibrary::setModules(const QStringList &modules)
{
    if (d->m_modules == modules)
        return;

    d->m_modules = modules;
    emit modulesChanged(d->m_modules);
}

QStringList BlockLibrary::modules() const
{
    return d->m_modules;
}

int BlockLibrary::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return static_cast<int>(d->m_rows.size());

    return 0;
}

QVariant BlockLibrary::data(const QModelIndex &index, int role) const
{
    if (hasIndex(index.row(), index.column(), index.parent())) {
        switch (static_cast<DataRole>(role)) {
        case DisplayRole:
        case ElementNameRole:
            return d->m_rows[index.row()].type.elementName();
        case ModuleNameRole:
            return d->m_rows[index.row()].type.module();
        case TypeNameRole:
            return d->m_rows[index.row()].type.elementName();
        case PrototypeRole:
            return qVariantFromValue(d->m_rows[index.row()].prototype.data());
        }
    }

    return {};
}

void BlockLibrary::classBegin()
{}

void BlockLibrary::componentComplete()
{
    reload();

    connect(this, &BlockLibrary::modulesChanged, this, &BlockLibrary::reload);
}

void BlockLibrary::reload()
{
    const auto engine = qmlEngine(this);

    beginResetModel();
    d->m_rows.clear();

    for (const auto &type: QQmlMetaType::qmlTypes()) {
        // FIXME: find better way to exclude types
        if (type.metaObject() == &Block::staticMetaObject
                || type.metaObject() == &Expression::staticMetaObject
                || !d->m_modules.contains(type.module()))
            continue;

        if (type.metaObject() && type.metaObject()->inherits(&Block::staticMetaObject)) {
            if (const auto prototype = dynamic_cast<Block *>(type.create())) {
                d->m_rows.emplace_back(type, prototype);
                continue;
            }
        }

        if (type.isComposite() && !type.sourceUrl().isEmpty() && engine) {
            QQmlComponent component{engine, type.sourceUrl()};
            if (std::unique_ptr<QObject> object{component.create()}) {
                if (object->metaObject()->inherits(&Block::staticMetaObject)) {
                    d->m_rows.emplace_back(type, static_cast<Block *>(object.release()));
                    continue;
                }
            }
        }
    }

    const auto lessByName = [](const auto &lhs, const auto &rhs) {
        return std::make_tuple(lhs.type.elementName(), lhs.type.module())
                < std::make_tuple(rhs.type.elementName(), rhs.type.module());
    };
    std::sort(begin(d->m_rows), end(d->m_rows), lessByName);

    endResetModel();
    emit countChanged(rowCount());
}

} // namespace Core
} // namespace QtItches
