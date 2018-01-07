#include "qtitchesblockview.h"

#include "qtitchesblock.h"
#include "qtitchesblocklibrary.h"
#include "qtitchescategorymodel.h"
#include "qtitchesscript.h"

#include <QQmlInfo>
#include <QPointer>
#include <QQmlContext>

namespace QtItches {
namespace Controls {

namespace {

using Core::Block;
using Core::BlockLibrary;

const auto s_qmlShapePrefix = QByteArrayLiteral("import QtItches.Controls 1.0\n"
                                                "\n");
const auto s_qmlShapeSuffix = QByteArrayLiteral(" {\n"
                                                "    anchors.fill: parent\n"
                                                "    block: _qtItches_blockView_.block\n"
                                                "    scriptViews: _qtItches_blockViewContent_.scriptViews\n"
                                                "}\n");

const auto s_qmlContent = QByteArrayLiteral("import QtItches.Controls 1.0\n"
                                            "\n"
                                            "BlockViewContent {\n"
                                            "    id: contentView\n"
                                            "\n"
                                            "    anchors { fill: parent /*; margins: 5*/ }\n"
                                            "    block: _qtItches_blockView_.block\n"
                                            "    shape: _qtItches_blockView_.shape\n"
                                            "}");

template<typename Object, typename Property>
void updateProperty(Object *target, void (Object::*notify)(const Property &), Property *field, const Property &newValue)
{
    if (*field == newValue)
        return;

    *field = newValue;
    (target->*notify)(*field);
}

}

class BlockView::Private
{
public:
    QColor categoryColor() const;
    bool isCurrentBlock() const;
    QByteArray shapeName() const;

    void updateView(BlockView *q);
    void updateContentItem(BlockView *q);
    void updateShapeItem(BlockView *q);

    void updateImplicitWidth(BlockView *q);
    void updateImplicitHeight(BlockView *q);

    QPointer<Block> m_block;
    QPointer<BlockLibrary> m_library;
    QPointer<QQmlContext> m_context;
    QPointer<QQuickItem> m_contentItem;
    QPointer<QQuickItem> m_shapeItem;
    QByteArray m_shapeName;

    QColor m_baseColor;
    QColor m_borderColor;
    QColor m_shapeColor;
    QColor m_textColor;
};

BlockView::BlockView(QQuickItem *parent)
    : BlockDropArea{parent}
    , d{new Private}
{
    setFlag(ItemAcceptsDrops);

    connect(this, &BlockView::blockChanged, this, [this] {
        delete d->m_contentItem;
        d->updateView(this);
    });

    d->updateView(this);
}

BlockView::~BlockView()
{
    delete d;
}

void BlockView::setLibrary(Core::BlockLibrary *library)
{
    if (d->m_library == library)
        return;

    if (d->m_library)
        d->m_library->disconnect(this);

    d->m_library = library;

    if (d->m_library)
        connect(d->m_library, &QObject::destroyed, this, [this] { emit libraryChanged({}); });

    emit libraryChanged(d->m_library);
}

Core::BlockLibrary *BlockView::library() const
{
    if (d->m_library)
        return d->m_library;

    for (auto item = parentItem(); item; item = item->parentItem())
        if (const auto blockView = dynamic_cast<BlockView *>(item))
            return blockView->library();

    return {};
}

void BlockView::setBlock(Block *block)
{
    if (d->m_block == block)
        return;

    if (d->m_block)
        d->m_block->disconnect(this);

    d->m_block = block;

    if (d->m_block) {
        connect(d->m_block, &QObject::destroyed, this, [this] { emit blockChanged({}); });
        connect(d->m_block, &Block::categoryChanged, this, [this] { d->updateView(this); });
        connect(d->m_block, &Block::shapeChanged, this, [this] { d->updateShapeItem(this); });

        if (const auto script = d->m_block->script())
            connect(script, &Core::Script::currentBlockChanged, this, [this] { d->updateView(this); });
    }

    emit blockChanged(d->m_block);
}

Block *BlockView::block() const
{
    return d->m_block;
}

QQuickItem *BlockView::shape() const
{
    return d->m_shapeItem;
}

QColor BlockView::baseColor() const
{
    return d->m_baseColor;
}

QColor BlockView::borderColor() const
{
    return d->m_borderColor;
}

QColor BlockView::shapeColor() const
{
    return d->m_shapeColor;
}

QColor BlockView::textColor() const
{
    return d->m_textColor;
}

QFont BlockView::font() const
{
    QFont font;
    font.setPixelSize(12);
    return font;
}

QFont BlockView::editorFont() const
{
    QFont font;
    font.setPixelSize(11);
    return font;
}

BlockView *BlockView::qmlAttachedProperties(QObject *object)
{
    if (const auto context = qmlContext(object))
        if (const auto blockView = context->contextProperty("_qtItches_blockView_").value<BlockView *>())
            return blockView;

    static const auto fallback = [] {
        auto blockView = new BlockView{};
        blockView->setParent(qApp);
        return blockView;
    }();

    return fallback;
}

Core::Block *BlockView::createBlock(const QByteArray &typeInfo)
{
    if (const auto l = library())
        return l->createBlock(typeInfo, this);

    return {};
}

QVariantMap BlockView::createMimeData(const QJsonObject &typeInfo) const
{
    auto mimeData = BlockDropArea::createMimeData(typeInfo);

    if (d->m_block && !mimeData.isEmpty())
        mimeData["text/plain"] = d->m_block->toPlainText();

    return mimeData;
}

QColor BlockView::Private::categoryColor() const
{
    return CategoryModel::categoryColor(m_block ? m_block->category() : Block::UnknownCategory);
}

QByteArray BlockView::Private::shapeName() const
{
    if (m_block) {
        const auto key = QMetaEnum::fromType<Block::Shape>().valueToKey(m_block->shape());
        return QByteArray::fromRawData(key, qstrlen(key));
    }

    return {};
}

bool BlockView::Private::isCurrentBlock() const
{
    const auto script = m_block ? m_block->script() : nullptr;
    return script && script->currentBlock() == m_block;
}

void BlockView::Private::updateView(BlockView *q)
{
    const auto newBaseColor = categoryColor();
    const auto newShapeColor = newBaseColor.lighter(isCurrentBlock() ? 120 : 100);

#define UPDATE_PROPERTY(Property, Value) \
    updateProperty(q, &BlockView::Property##Changed, &m_##Property, Value)

    UPDATE_PROPERTY(baseColor, newBaseColor);
    UPDATE_PROPERTY(borderColor, newShapeColor.darker());
    UPDATE_PROPERTY(shapeColor, newShapeColor);
    UPDATE_PROPERTY(textColor, QColor{Qt::white});

#undef UPDATE_PROPERTY

    if (m_context.isNull()) {
        if (const auto context = qmlContext(q)) {
            m_context = new QQmlContext{context, q};
            m_context->setContextProperty("_qtItches_blockView_", q);
        }
    }

    if (m_shapeItem.isNull())
        updateShapeItem(q);
    if (m_contentItem.isNull())
        updateContentItem(q);
}

void BlockView::Private::updateContentItem(BlockView *q)
{
    if (!m_context || !m_context->engine())
        return;

    QQmlComponent component{m_context->engine()};
    component.setData(s_qmlContent, m_context->baseUrl());
    if (component.status() == QQmlComponent::Error) {
        qmlWarning(q, component.errors());
        return;
    }

    const auto object = component.create(m_context);
    if (const auto item = dynamic_cast<QQuickItem *>(object)) {
        delete std::exchange(m_contentItem, item);
        m_context->setContextProperty("_qtItches_blockViewContent_", m_contentItem.data());
        m_contentItem->setParentItem(q);
        m_contentItem->setParent(q);

        connect(m_contentItem, &QQuickItem::implicitWidthChanged, q, [this, q] { updateImplicitWidth(q); });
        connect(m_contentItem, &QQuickItem::implicitHeightChanged, q, [this, q] { updateImplicitHeight(q); });

        updateImplicitWidth(q);
        updateImplicitHeight(q);
    }
}

void BlockView::Private::updateShapeItem(BlockView *q)
{
    if (!m_context || !m_context->engine())
        return;

    const auto new_shapeName = shapeName();
    if (m_shapeName != new_shapeName) {
        QQmlComponent component{m_context->engine()};
        const auto shapeQml = s_qmlShapePrefix + new_shapeName + s_qmlShapeSuffix;
        component.setData(shapeQml, m_context->baseUrl());
        if (component.status() == QQmlComponent::Error) {
            qmlWarning(q, component.errors());
            return;
        }

        const auto object = component.create(m_context);
        if (const auto item = dynamic_cast<QQuickItem *>(object)) {
            m_shapeName = new_shapeName;
            delete std::exchange(m_shapeItem, item);
            m_shapeItem->setParentItem(q);
            m_shapeItem->setParent(q);

            updateImplicitWidth(q);
            updateImplicitHeight(q);

            emit q->shapeChanged(m_shapeItem);
        }
    }
}

void BlockView::Private::updateImplicitWidth(BlockView *q)
{
    const qreal implicitWidth = m_contentItem ? m_contentItem->implicitWidth() : 0;
    const qreal minimumWidth = m_block && m_block->shape() == Core::Block::StackShape ? 100 : 0;
    q->setImplicitWidth(qMax(implicitWidth, minimumWidth));
}

void BlockView::Private::updateImplicitHeight(BlockView *q)
{
    q->setImplicitHeight(m_contentItem ? m_contentItem->implicitHeight() : 0);
}

} // namespace Controls
} // namespace QtItches
