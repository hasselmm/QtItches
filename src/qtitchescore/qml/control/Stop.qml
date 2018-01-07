import QtItches.Core 1.0

Block {
    id: stop

    property alias target: targetParameter.currentIndex

    category: Block.ControlCategory
    connectors: Block.TopConnector

    parameters: [
        ConstantParameter {
            string: QT_TR_NOOP("stop")
        },

        ChoiceParameter {
            id: targetParameter

            currentIndex: 1
            model: [
                QT_TR_NOOP("all"),
                QT_TR_NOOP("this script"),
                QT_TR_NOOP("other scripts in sprite")
            ]
        }
    ]

    function run() {
        switch (target) {
        case 0:
            project.stop();
            break;

        case 1:
            script.stop();
            break;

        case 2:
            context.stopAllButThis(script);
            break;

        default:
            throw "Unsupported target: %1".arg(target);
        }
    }
}
