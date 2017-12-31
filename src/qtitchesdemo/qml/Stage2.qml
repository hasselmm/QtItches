import QtItches.Core 1.0

Stage {
    name: "Test 2"

    Actor {
        name: "Evolution Robot"

        Script {
            WhenThisSpriteClicked {}

            If {}
            IfElse {}
            Repeat {}
//            RepeatUntil {}
            Forever {}

/*
            WaitSecs { seconds: 1.1 }
            Repeat {
                count: 3
                sequence: Script {
                    objectName: "repeat"
                    Say { text: "Hello World!" }
                    WaitSecs { seconds: 1.2 }
                    Say { text: "How are you?" }
                    Think { text: "Feeling well?" }
                    WaitSecs { seconds: 1.3 }
                    Think {}
                }
            }

            Not {}
            Or {}
            KeyPressed {}
            MouseDown {}
            Stop {}
*/
        }
    }
}
