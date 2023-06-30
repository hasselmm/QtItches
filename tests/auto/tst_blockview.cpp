#include "qtitchesblocklibrary.h"
#include "qtitchesblockview.h"

#include <QMimeData>
#include <QQmlContext>
#include <QQmlEngine>
#include <QSignalSpy>
#include <QStaticPlugin>
#include <QTest>

static void initResources()
{
    Q_INIT_RESOURCE(qtitchescontrolsplugin);
    Q_INIT_RESOURCE(qtitchescoreplugin);
}

Q_IMPORT_PLUGIN(qtitchescontrolsplugin)
Q_IMPORT_PLUGIN(qtitchescoreplugin)

namespace QTest {

template<> inline char *toString(const QtItches::Controls::BlockView::DropActions &actions)
{
    QString buffer;
    QDebug(&buffer) << actions;
    return qstrdup(buffer.toLocal8Bit().constData());
}

}

namespace QtItches {
namespace Controls {

class BlockViewTest : public QObject
{
    Q_OBJECT

public:
    BlockViewTest()
    {
        initResources();
    }

private slots:
    void testDropBehavior_data()
    {
        QTest::addColumn<QString>("blockQml");
        QTest::addColumn<QVector<int>>("pendingDropActionChanges");
        QTest::addColumn<BlockView::DropActions>("acceptedDropActions");
        QTest::addColumn<BlockView::DropAction>("topRegionActions");
        QTest::addColumn<BlockView::DropAction>("bottomRegionActions");

        QTest::newRow("GotoXY")
                << "GotoXY {}"
                << QVector<int>{0, 1, 2, 3, 4, 5, 6}
                << BlockView::DropActions{BlockView::PrependBlock | BlockView::AppendBlock}
                << BlockView::PrependBlock
                << BlockView::AppendBlock;

        QTest::newRow("DoForever")
                << "DoForever {}"
                << QVector<int>{0, 1, 2, 2, 2, 3, 4}
                << BlockView::DropActions{BlockView::PrependBlock}
                << BlockView::PrependBlock
                << BlockView::DropAction{};

        QTest::newRow("WhenFlagClicked")
                << "WhenFlagClicked {}"
                << QVector<int>{0, 0, 1, 2, 3, 4, 4}
                << BlockView::DropActions{BlockView::AppendBlock}
                << BlockView::DropAction{}
                << BlockView::AppendBlock;

        QTest::newRow("Not")
                << "Not {}"
                << QVector<int>{0, 0, 0, 0, 0, 0, 0}
                << BlockView::DropActions{}
                << BlockView::DropAction{}
                << BlockView::DropAction{};
    }

    void testDropBehavior()
    {
        QFETCH(QString, blockQml);
        QFETCH(QVector<int>, pendingDropActionChanges);
        QFETCH(BlockView::DropActions, acceptedDropActions);
        QFETCH(BlockView::DropAction, topRegionActions);
        QFETCH(BlockView::DropAction, bottomRegionActions);

        QQmlEngine engine;
        engine.addImportPath("qrc:/imports");

        QQmlComponent component{&engine};
        component.setData("import QtItches.Core 1.0\n"
                          "import QtItches.Controls 1.0\n"
                          "BlockView {\n"
                          "    block: " + blockQml.toUtf8() + "\n"
                          "    library: BlockLibrary {}\n"
                          "}", {});

        QVERIFY2(component.status() == QQmlComponent::Ready, qPrintable(component.errorString()));
        const auto blockView = dynamic_cast<BlockView *>(component.create());
        QVERIFY(blockView);

        QSignalSpy pendingDropActionChanged{blockView, &BlockView::pendingDropActionChanged};

        QVERIFY(qmlContext(blockView));
        QVERIFY(blockView->block());
        QVERIFY(blockView->library());
        QVERIFY(!blockView->size().isEmpty());
        QCOMPARE(blockView->acceptedDropActions(), acceptedDropActions);
        QCOMPARE(blockView->pendingDropAction(), BlockView::DropAction{});
        QCOMPARE(pendingDropActionChanged.count(), pendingDropActionChanges.takeFirst());

        const auto typeInfo = blockView->library()->typeInfo("QtItches.Core", 1, 0, "TurnLeft");
        QVERIFY(!typeInfo.isEmpty());

        const auto qmlMimeData = blockView->createMimeData(typeInfo);
        const auto mimeData = std::make_unique<QMimeData>();
        for (auto it = qmlMimeData.begin(), last = qmlMimeData.end(); it != last; ++it)
            mimeData->setData(it.key(), it.value().toByteArray());
        QVERIFY(!mimeData->text().isEmpty());

#define VERIFY_DRAG_EVENT_WITHOUT_RECT(expectedFloatingActions, expectedPendingActions, expectAccepted) do { \
    QCOMPARE(pendingDropActionChanged.count(), pendingDropActionChanges.takeFirst()); \
    QCOMPARE(blockView->floatingDropActions(), (expectedFloatingActions)); \
    QCOMPARE(blockView->pendingDropAction(), (expectedPendingActions)); \
    QCOMPARE(event.isAccepted(), (expectAccepted)); \
    } while(false)

#define VERIFY_DRAG_EVENT(expectedFloatingActions, expectedPendingActions, expectAccepted) do { \
    VERIFY_DRAG_EVENT_WITHOUT_RECT(expectedFloatingActions, expectedPendingActions, expectAccepted); \
    QCOMPARE(event.answerRect().height() > 1, (expectAccepted)); \
    } while(false)

        const QPoint topPoint{1, 1};
        const QPoint bottomPoint{1, qRound(blockView->height()) - 2};

        { // enter from top
            QDragEnterEvent event{topPoint, Qt::CopyAction, mimeData.get(), Qt::LeftButton, {}};
            qApp->sendEvent(blockView, &event);

            VERIFY_DRAG_EVENT(bottomRegionActions | topRegionActions,
                              topRegionActions, !!topRegionActions);
        }

        { // move to bottom
            QDragMoveEvent event{bottomPoint, Qt::CopyAction, mimeData.get(), Qt::LeftButton, {}};
            qApp->sendEvent(blockView, &event);

            VERIFY_DRAG_EVENT(bottomRegionActions | topRegionActions,
                              bottomRegionActions, !!bottomRegionActions);
        }

        { // leave
            QDragLeaveEvent event;
            qApp->sendEvent(blockView, &event);
            VERIFY_DRAG_EVENT_WITHOUT_RECT(0, 0, true);
        }

        { // enter from bottom
            QDragEnterEvent event{bottomPoint, Qt::CopyAction, mimeData.get(), Qt::LeftButton, {}};
            qApp->sendEvent(blockView, &event);

            VERIFY_DRAG_EVENT(bottomRegionActions | topRegionActions,
                              bottomRegionActions, !!bottomRegionActions);
        }

        { // move to top
            QDragMoveEvent event{topPoint, Qt::CopyAction, mimeData.get(), Qt::LeftButton, {}};
            qApp->sendEvent(blockView, &event);

            VERIFY_DRAG_EVENT(bottomRegionActions | topRegionActions,
                              topRegionActions, !!topRegionActions);
        }

        { // drop
            QDropEvent event{topPoint, Qt::CopyAction, mimeData.get(), Qt::LeftButton, {}};
            qApp->sendEvent(blockView, &event);

            VERIFY_DRAG_EVENT_WITHOUT_RECT(0, 0, !!topRegionActions);
        }
    }
};

} // namespace Controls
} // namespace QtItches

QTEST_MAIN(QtItches::Controls::BlockViewTest)

#include "tst_blockview.moc"
