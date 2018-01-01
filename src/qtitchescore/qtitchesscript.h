#ifndef QTITCHESSCRIPT_H
#define QTITCHESSCRIPT_H

#include <QQmlListProperty>
#include <QQmlParserStatus>

namespace QtItches {
namespace Core {

class Actor;
class Block;
class Stage;

class Script : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_CLASSINFO("DefaultProperty", "blocks")

    Q_PROPERTY(QtItches::Core::Actor *actor READ actor CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Script *scope READ scope CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Stage *stage READ stage CONSTANT FINAL)

    Q_PROPERTY(QQmlListProperty<QtItches::Core::Block> blocks READ blocks CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Block *currentBlock READ currentBlock NOTIFY currentBlockChanged FINAL)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged FINAL)

public:
    explicit Script(QObject *parent = {});
    ~Script();

    Actor *actor() const;
    Script *scope() const;
    Stage *stage() const;

    QQmlListProperty<Block> blocks();
    Block *currentBlock() const;
    bool running() const;

    // QQmlParserStatus interface
    void classBegin() override;
    void componentComplete() override;

public slots:
    bool run();
    void stop();

signals:
    void runningChanged(bool running);
    void currentBlockChanged(QtItches::Core::Block *currentBlock);
    void finished();

private:
    class Private;
    Private *const d;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESSCRIPT_H
