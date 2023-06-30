#include "qtitchesblocklibrary.h"

#include "qtitchesblock.h"
#include "qtitchesexpression.h"
#include "qtitchesscriptcontext.h"
#include "qtitchesutils.h"

#include <private/qhashedstring_p.h>
#include <private/qqmlmetatype_p.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QPointer>
#include <QQmlComponent>

#include <memory>

namespace QtItches {
namespace Core {

namespace {
constexpr auto s_typeId = "typeId"_l1;
constexpr auto s_typeCategory = "typeCategory"_l1;
constexpr auto s_elementName = "elementName"_l1;
constexpr auto s_moduleUri = "moduleUri"_l1;
}

class BlockLibrary::Private
{
public:
    struct Row
    {
        Row() = default;
        Row(const QQmlType &type, Block *prototype)
            : type{type}, prototype{prototype} {}

        QString moduleUri() const
        {
            return type.module() + ' ' + QString::number(type.majorVersion()) + '.' + QString::number(type.majorVersion());
        }

        QJsonObject createTypeInfo() const
        {
            return {
                {s_typeId, type.index()},
                {s_typeCategory, prototype->typeCategory()},
                {s_elementName, type.elementName()},
                {s_moduleUri, moduleUri()},
            };
        }

        QQmlType type;
        QPointer<Block> prototype;
    };

    Block *createBlock(QQmlEngine *engine, const QQmlType &type) const;

    std::vector<Row> m_rows;
    QStringList m_modules = {"QtItches.Core"};
    QPointer<ScriptContext> m_context;
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

void BlockLibrary::setContext(ScriptContext *context)
{
    if (d->m_context == context)
        return;

    d->m_context = context;

    for (const auto &row: d->m_rows) {
        if (row.prototype)
            row.prototype->setContext(d->m_context);
    }

    emit contextChanged(d->m_context);
}

ScriptContext *BlockLibrary::context() const
{
    return d->m_context;
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
        case ModuleUriRole:
            return d->m_rows[index.row()].moduleUri();
        case TypeNameRole:
            return d->m_rows[index.row()].type.elementName();
        case PrototypeRole:
            return QVariant::fromValue(d->m_rows[index.row()].prototype.data());
        case TypeInfoRole:
            return d->m_rows[index.row()].createTypeInfo();
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

Block::TypeCategory BlockLibrary::typeCategory(const QJsonObject &typeInfo)
{
    return static_cast<Block::TypeCategory>(typeInfo.value(s_typeCategory).toInt());
}

QJsonObject BlockLibrary::typeInfo(const QString &uri, int majorVersion, int minorVersion, const QString &name)
{
    const QHashedString hashedUri{uri};

    for (const auto &row: d->m_rows) {
        if (row.type.module() == hashedUri
                && row.type.majorVersion() == majorVersion
                && row.type.minorVersion() == minorVersion
                && row.type.elementName() == name)
            return row.createTypeInfo();
    }

    return {};
}

Block *BlockLibrary::Private::createBlock(QQmlEngine *engine, const QQmlType &type) const
{
    if (type.metaObject() && type.metaObject()->inherits(&Block::staticMetaObject)) {
        if (std::unique_ptr<QObject> object{type.create()})
            if (object->metaObject()->inherits(&Block::staticMetaObject))
                return static_cast<Block *>(object.release());
    }

    if (type.isComposite() && !type.sourceUrl().isEmpty() && engine) {
        QQmlComponent component{engine, type.sourceUrl()};
        if (std::unique_ptr<QObject> object{component.create()})
            if (object->metaObject()->inherits(&Block::staticMetaObject))
                return static_cast<Block *>(object.release());
    }

    return {};
}

Block *BlockLibrary::createBlock(const QByteArray &typeInfo, QObject *parent) const
{
    const auto typeId = QJsonDocument::fromJson(typeInfo).object().value(s_typeId).toInt();

    for (const auto &row: d->m_rows) {
        if (row.type.index() == typeId) {
            if (const auto block = d->createBlock(qmlEngine(this), row.type)) {
                block->setParent(parent);
                return block;
            }
        }
    }

    return {};
}

void BlockLibrary::reload()
{
    beginResetModel();
    d->m_rows.clear();

    const auto engine = qmlEngine(this);
    const auto knownQmlTypes = QQmlMetaType::qmlTypes();
    for (const auto &type: knownQmlTypes) {
        if (type.metaObject() == &Block::staticMetaObject
                || type.metaObject() == &Expression::staticMetaObject
                || type.metaObject() == &UnaryExpression::staticMetaObject
                || type.metaObject() == &BinaryExpression::staticMetaObject
                || !d->m_modules.contains(type.module()))
            continue; // FIXME: find better way to exclude types - classinfo ?

        if (const auto prototype = d->createBlock(engine, type)) {
            prototype->setContext(d->m_context);
            d->m_rows.emplace_back(type, prototype);
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
