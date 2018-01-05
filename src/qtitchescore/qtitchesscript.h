#ifndef QTITCHESSCRIPT_H
#define QTITCHESSCRIPT_H

#include <QQmlListProperty>
#include <QQmlParserStatus>

namespace QtItches {
namespace Core {

class Block;
class Project;
class ScriptContext;
class Sprite;
class Stage;

class Script : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_CLASSINFO("DefaultProperty", "blocks")

    Q_PROPERTY(QtItches::Core::ScriptContext *context READ context CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Script *parentScript READ parentScript CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Project *project READ project CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Sprite *sprite READ sprite CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Stage *stage READ stage CONSTANT FINAL)

    Q_PROPERTY(QQmlListProperty<QtItches::Core::Block> blocks READ blocks CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Block *currentBlock READ currentBlock NOTIFY currentBlockChanged FINAL)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged FINAL)

public:
    explicit Script(QObject *parent = {});
    ~Script();

    Script *parentScript() const;
    ScriptContext *context() const;
    Project *project() const;
    Sprite *sprite() const;
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
