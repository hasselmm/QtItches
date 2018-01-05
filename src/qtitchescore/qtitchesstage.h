#ifndef QTITCHESSTAGE_H
#define QTITCHESSTAGE_H

#include <QQmlListProperty>

namespace QtItches {
namespace Core {

class Sprite;

class Stage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QQmlListProperty<QtItches::Core::Sprite> sprites READ sprites CONSTANT FINAL)
    Q_CLASSINFO("DefaultProperty", "sprites")

public:
    Stage(QObject *parent = {});
    ~Stage();

    QQmlListProperty<Sprite> sprites();

    void setName(const QString &name);
    QString name() const;

public:
    void stop();

signals:
    void flagClicked(QObject *source);
    void nameChanged(const QString &name);

private:
    class Private;
    Private *const d;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESSTAGE_H
