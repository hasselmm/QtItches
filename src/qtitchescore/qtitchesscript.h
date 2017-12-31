#ifndef QTITCHESSCRIPT_H
#define QTITCHESSCRIPT_H

#include <QQmlListProperty>
#include <QQmlParserStatus>

namespace QtItches {

class Actor;
class Block;
class Stage;

class Script : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_CLASSINFO("DefaultProperty", "blocks")

    Q_PROPERTY(QtItches::Actor *actor READ actor CONSTANT FINAL)
    Q_PROPERTY(QtItches::Script *scope READ scope CONSTANT FINAL)
    Q_PROPERTY(QtItches::Stage *stage READ stage CONSTANT FINAL)

    Q_PROPERTY(QQmlListProperty<QtItches::Block> blocks READ blocks CONSTANT FINAL)
    Q_PROPERTY(QtItches::Block *currentBlock READ currentBlock NOTIFY currentBlockChanged FINAL)
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
    void currentBlockChanged(QtItches::Block *currentBlock);
    void finished();

private:
    class Private;
    Private *const d;
};

} // namespace QtItches

#endif // QTITCHESSCRIPT_H
