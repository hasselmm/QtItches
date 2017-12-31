import QtItches.Core 1.0

Stage {
    name: "Test 1"

    Actor {
        name: "Evolution Robot"

        costumes: [
            "qrc:/assets/cat1.svg",
            "qrc:/assets/cat2.svg",
        ]

        Script {
            WhenThisSpriteClicked {}
            WaitSecs { seconds: Multiply { left: Plus { left: 1.2; right: 1.3 } right: 3 } }

            Forever {
                loop: Script {
                    Say { text: "Hello World!" }
                    WaitSecs { seconds: 1.2 }
                    Say { text: "How are you?" }
                    WaitSecs { seconds: 1.3 }

                    IfElse {
                        //condition: LessThan { left: 1; right: 2 }
                        onTrue: Script { Say { text: "Yes!" } }
                        onFalse: Script { Say { text: "No!" } }
                    }

                    WaitSecs { seconds: 1.4 }
                }
            }
        }

        Script {
            WhenThisSpriteClicked {}

            Repeat {
                count: Plus { left: 1; right: 2 }
                loop: Script {
                    Say { text: "Hello World!" }
                    WaitSecs { seconds: 1.2 }
                    Say { text: "How are you?" }
                    Think { text: "Feeling well?" }
                    WaitSecs { seconds: 1.3 }
                    Think {}
                }
            }

            Stop {}
        }
    }
}
