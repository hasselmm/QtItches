#ifndef QTITCHESBLOCKLIBRARY_H
#define QTITCHESBLOCKLIBRARY_H

#include "qtitchesutils.h"

#include <QAbstractListModel>
#include <QQmlParserStatus>

namespace QtItches {
namespace Core {

class ScriptContext;

class BlockLibrary : public QAbstractListModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged FINAL)
    Q_PROPERTY(QStringList modules READ modules WRITE setModules NOTIFY modulesChanged FINAL)
    Q_PROPERTY(QtItches::Core::ScriptContext *context READ context WRITE setContext NOTIFY contextChanged FINAL)

public:
    enum DataRole {
        DisplayRole = Qt::DisplayRole,
        PrototypeRole = Qt::UserRole,
        ElementNameRole,
        ModuleNameRole,
        TypeNameRole,
    };

    QTITCHES_DATAROLE(DataRole)
    explicit BlockLibrary(QObject *parent = {});
    ~BlockLibrary();

    void setModules(const QStringList &modules);
    QStringList modules() const;

    void setContext(ScriptContext *context);
    ScriptContext *context() const;

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // QQmlParserStatus interface
    void classBegin() override;
    void componentComplete() override;

public slots:
    void reload();

signals:
    void countChanged(int count);
    void modulesChanged(const QStringList modules);
    void contextChanged(QtItches::Core::ScriptContext *context);

private:
    class Private;
    Private *const d;
};

} // namespace Core
} // namespace QtItches

#endif // QTITCHESBLOCKLIBRARY_H
