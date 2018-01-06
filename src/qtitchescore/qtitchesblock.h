#ifndef QTITCHESBLOCK_H
#define QTITCHESBLOCK_H

#include <QQmlListProperty>
#include <QQmlParserStatus>

namespace QtItches {
namespace Core {

class Parameter;
class Project;
class Script;
class ScriptContext;
class Sprite;
class Stage;

class Block : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "data")
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QtItches::Core::ScriptContext *context READ context NOTIFY contextChanged FINAL)
    Q_PROPERTY(QtItches::Core::Sprite *sprite READ sprite NOTIFY contextChanged FINAL)
    Q_PROPERTY(QtItches::Core::Stage *stage READ stage NOTIFY contextChanged FINAL)

    Q_PROPERTY(QtItches::Core::Project *project READ project CONSTANT FINAL)
    Q_PROPERTY(QtItches::Core::Script *script READ script CONSTANT FINAL)

    Q_PROPERTY(bool available READ available WRITE setAvailable NOTIFY availableChanged FINAL)
    Q_PROPERTY(int category READ category WRITE setCategory NOTIFY categoryChanged FINAL)
    Q_PROPERTY(int connectors READ connectors WRITE setConnectors NOTIFY connectorsChanged FINAL)
    Q_PROPERTY(int shape READ shape WRITE setShape NOTIFY shapeChanged FINAL)

    Q_PROPERTY(QQmlListProperty<QObject> data READ data CONSTANT FINAL)
    Q_PROPERTY(QQmlListProperty<QtItches::Core::Parameter> parameters READ parameters NOTIFY parametersChanged FINAL)

public:
    enum Category {
        UnknownCategory = 0,
        ControlCategory = 1,
        EventsCategory,
        LooksCategory,
        MotionCategory,
        OperatorsCategory,
        PenCategory,
        SensingCategory,
        SoundCategory,
        DataCategory,
    };

    Q_ENUM(Category)

    enum Connector {
        TopConnector = 1,
        BottomConnector = 2,
    };

    Q_FLAG(Connector)
    Q_DECLARE_FLAGS(Connectors, Connector)

    enum Shape {
        BooleanShape,
        ReporterShape,
        StackShape,
    };

    Q_ENUM(Shape)

    explicit Block(QObject *parent = {});
    ~Block();

    void setContext(ScriptContext *context);
    ScriptContext *context() const;
    Project *project() const;
    Sprite *sprite() const;
    Script *script() const;
    Stage *stage() const;

    void setAvailable(bool available);
    bool available() const;

    void setCategory(Category category);
    Category category() const;

    void setConnectors(Connectors connectors);
    Connectors connectors() const;

    void setShape(Shape shape);
    Shape shape() const;

    QQmlListProperty<QObject> data();
    QQmlListProperty<Parameter> parameters();

    // QQmlParserStatus interface
    void classBegin() override;
    void componentComplete() override;

public slots:
    virtual void run();
    virtual void stop();

signals:
    void availableChanged(bool available);
    void categoryChanged(int category);
    void connectorsChanged(int connectors);
    void shapeChanged(int shape);
    void parametersChanged();
    void contextChanged();
    void finished();

protected:
    Parameter *parameter(int index) const;
    template<class T> T *parameter(int index) const { return dynamic_cast<T *>(parameter(index)); }
    void resetParameters(QList<Parameter *> &&parameters);

private:
    void setCategory(int category) { setCategory(static_cast<Category>(category)); }
    void setConnectors(int connectors) { setConnectors(static_cast<Connectors>(connectors)); }
    void setShape(int shape) { setShape(static_cast<Shape>(shape)); }

    class Private;
    Private *const d;
};

} // namespace Core
} // namespace QtItches

Q_DECLARE_OPERATORS_FOR_FLAGS(QtItches::Core::Block::Connectors)

#endif // QTITCHESBLOCK_H
