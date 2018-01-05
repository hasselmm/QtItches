import QtItches.Core 1.0

Project {
    name: "Run in Square"

    Sprite {
        name: "Magnesus"

        costumes: [
            "qrc:/assets/magnesus-1.svg",
            "qrc:/assets/magnesus-2.svg",
            "qrc:/assets/magnesus-3.svg",
            "qrc:/assets/magnesus-4.svg",
            "qrc:/assets/magnesus-5.svg",
            "qrc:/assets/magnesus-6.svg",
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

                        then: Script {
                            ThinkForSecs { text: "Uch..."; seconds: 1 }
                            TurnRight {}
                        }
                    }

                    DoIf {
                        condition: And {
                            left: LessThan { left: YPos {} right: -100 }
                            right: Equals { left: Direction {} right: 180 }
                        }

                        then: Script {
                            ThinkForSecs { text: "Ach..."; seconds: 1 }
                            TurnRight {}
                        }
                    }

                    DoIf {
                        condition: And {
                            left: LessThan { left: XPos {} right: -100 }
                            right: Equals { left: Direction {} right: -90 }
                        }

                        then: Script {
                            ThinkForSecs { text: "Eh..."; seconds: 1 }
                            TurnRight {}
                        }
                    }

                    DoIf {
                        condition: And {
                            left: GreaterThan { left: YPos {} right: 100 }
                            right: Equals { left: Direction {} right: 0 }
                        }

                        then: Script {
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
