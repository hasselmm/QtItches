import QtItches.Core 1.0

Block {
    id: stop

    property alias target: targetParameter.currentIndex

    category: Block.ControlCategory
    connectors: Block.TopConnector

    parameters: [
        ConstantParameter {
            string: qsTr("stop")
        },

        ChoiceParameter {
            id: targetParameter

            currentIndex: 1
            model: [
                qsTr("all"),
                qsTr("this script"),
                qsTr("other scripts in sprite")
            ]
        }
    ]

    function run() {
        switch (target) {
        case 0:
            actor.stop();
            break;

        case 1:
            script.stop();
            break;

        case 2:
            actor.stopAllExceptThis(script);
            break;

        default:
            throw "Unsupported target: %1".arg(target);
        }
    }
}
