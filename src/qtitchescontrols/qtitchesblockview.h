#ifndef QTITCHESBLOCKVIEW_H
#define QTITCHESBLOCKVIEW_H

#include <QQuickItem>

namespace QtItches {

namespace Core {
class Block;
}

namespace Controls {

class BlockView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QtItches::Core::Block *block READ block WRITE setBlock NOTIFY blockChanged FINAL)
    Q_PROPERTY(QQuickItem *shape READ shape NOTIFY shapeChanged FINAL)

    Q_PROPERTY(QColor baseColor READ baseColor NOTIFY baseColorChanged FINAL)
    Q_PROPERTY(QColor borderColor READ borderColor NOTIFY borderColorChanged FINAL)
    Q_PROPERTY(QColor shapeColor READ shapeColor NOTIFY shapeColorChanged FINAL)
    Q_PROPERTY(QColor textColor READ textColor NOTIFY textColorChanged FINAL)

    Q_PROPERTY(QFont font READ font CONSTANT FINAL)
    Q_PROPERTY(QFont editorFont READ editorFont CONSTANT FINAL)

public:
    explicit BlockView(QQuickItem *parent = {});
    ~BlockView();

    void setBlock(Core::Block *block);
    Core::Block *block() const;

    QQuickItem *shape() const;

    QColor baseColor() const;
    QColor borderColor() const;
    QColor shapeColor() const;
    QColor textColor() const;

    QFont font() const;
    QFont editorFont() const;

signals:
    void blockChanged(Core::Block *block);
    void shapeChanged(QQuickItem *shape);

    void baseColorChanged(const QColor &baseColor);
    void borderColorChanged(const QColor &borderColor);
    void shapeColorChanged(const QColor &shapeColor);
    void textColorChanged(const QColor &textColor);

private:
    class Private;
    Private *const d;
};

} // namespace Controls
} // namespace QtItches

#endif // QTITCHESBLOCKVIEW_H
