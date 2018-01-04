import QtItches.Core 1.0

Stage {
    name: "Run in Square"

    Sprite {
        name: "Cat"

        costumes: [
            "qrc:/assets/cat1.svg",
            "qrc:/assets/cat2.svg",
        ]

        Script {
            WhenFlagClicked {}
            GotoXY { x: 0; y: 0 }
            TurnTo { direction: 90 }

            DoForever {
                loop: Script {
                    DoIf {
                        condition: And {
                            left: GreaterThan { left: XPos {} right: 100 }
                            right: Equals { left: Direction {} right: 90 }
                        }

                        onTrue: Script {
                            ThinkForSecs { text: "Uch..."; seconds: 1 }
                            TurnRight {}
                        }
                    }

                    DoIf {
                        condition: And {
                            left: LessThan { left: YPos {} right: -100 }
                            right: Equals { left: Direction {} right: 180 }
                        }

                        onTrue: Script {
                            ThinkForSecs { text: "Ach..."; seconds: 1 }
                            TurnRight {}
                        }
                    }

                    DoIf {
                        condition: And {
                            left: LessThan { left: XPos {} right: -100 }
                            right: Equals { left: Direction {} right: -90 }
                        }

                        onTrue: Script {
                            ThinkForSecs { text: "Eh..."; seconds: 1 }
                            TurnRight {}
                        }
                    }

                    DoIf {
                        condition: And {
                            left: GreaterThan { left: YPos {} right: 100 }
                            right: Equals { left: Direction {} right: 0 }
                        }

                        onTrue: Script {
                            SayForSecs { text: "Omm!"; seconds: 1 }
                            TurnRight {}
                        }
                    }

                    GoForward { steps: 10 }
                }
            }
        }
    }
}
