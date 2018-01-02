#include "qtitchesblockview.h"

#include "qtitchesblock.h"
#include "qtitchesscript.h"

#include <QQmlInfo>
#include <QPointer>
#include <QQmlContext>

namespace QtItches {
namespace Controls {

namespace {

using Core::Block;

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

const QColor s_controlCategoryColor{"#e1a91a"};
const QColor s_eventsCategoryColor{"#c88330"};
const QColor s_listsCategoryColor{"#ca5c2c"};
const QColor s_looksCategoryColor{"#8a55d7"};
const QColor s_motionsCategoryColor{"#4a6cd4"};
const QColor s_operatorsCategoryColor{"#5cb712"};
const QColor s_sensingCategoryColor{"#2ca5e2"};
const QColor s_soundsCategoryColor{"#bb42c3"};
const QColor s_unknownCategoryColor{"#4d4b60"};
const QColor s_variablesCategoryColor{"#ee7d16"};

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
    void updateHeaderRow(BlockView *q);
    void updateShapeItem(BlockView *q);

    void updateImplicitWidth(BlockView *q);
    void updateImplicitHeight(BlockView *q);

    QPointer<Block> m_block;
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
    : QQuickItem{parent}
    , d{new Private}
{
    connect(this, &BlockView::blockChanged, this, [this] { d->updateView(this); });
    d->updateView(this);
}

BlockView::~BlockView()
{
    delete d;
}

void BlockView::setBlock(Block *block)
{
    if (d->m_block == block)
        return;

    if (d->m_block)
        d->m_block->disconnect(this);

    d->m_block = block;

    if (d->m_block) {
        connect(d->m_block, &Block::destroyed, this, [this] { emit blockChanged({}); });
        connect(d->m_block, &Block::categoryChanged, this, [this] { d->updateView(this); });

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

QColor BlockView::Private::categoryColor() const
{
    if (m_block) {
        switch (m_block->category()) {
        case Block::ControlCategory:
            return s_controlCategoryColor;
        case Block::EventsCategory:
            return s_eventsCategoryColor;
        case Block::ListsCategory:
            return s_listsCategoryColor;
        case Block::LooksCategory:
            return s_looksCategoryColor;
        case Block::MotionsCategory:
            return s_motionsCategoryColor;
        case Block::OperatorsCategory:
            return s_operatorsCategoryColor;
        case Block::SensingCategory:
            return s_sensingCategoryColor;
        case Block::SoundsCategory:
            return s_soundsCategoryColor;
        case Block::VariablesCategory:
            return s_variablesCategoryColor;
        case Block::UnknownCategory:
            break;
        }
    }

    return s_unknownCategoryColor;
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

    if (m_context && m_context->engine()) {
        updateShapeItem(q);
        updateHeaderRow(q);
    }
}

void BlockView::Private::updateHeaderRow(BlockView *q)
{
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

        connect(m_contentItem, &QQuickItem::implicitWidthChanged, q, [this, q] { updateImplicitWidth(q); });
        connect(m_contentItem, &QQuickItem::implicitHeightChanged, q, [this, q] { updateImplicitHeight(q); });

        updateImplicitWidth(q);
        updateImplicitHeight(q);
    }
}

void BlockView::Private::updateShapeItem(BlockView *q)
{
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
            delete std::exchange(m_shapeItem, item);
            m_shapeItem->setParentItem(q);
            m_shapeName = new_shapeName;

            updateImplicitWidth(q);
            updateImplicitHeight(q);

            emit q->shapeChanged(m_shapeItem);
        }
    }
}

void BlockView::Private::updateImplicitWidth(BlockView *q)
{
    q->setImplicitWidth(m_contentItem ? m_contentItem->implicitWidth() : 0);
}

void BlockView::Private::updateImplicitHeight(BlockView *q)
{
    q->setImplicitHeight(m_contentItem ? m_contentItem->implicitHeight() : 0);
}

} // namespace Controls
} // namespace QtItches
