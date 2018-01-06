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
                    WaitSecs { seconds: Divide { left: 1; right: 30 } }
                    // Comment { text: "Slow down until issue #18 got resolved" }
                }
            }
        }
    }

    Sprite {
        name: "Blue Creature"

        costumes: [
            "qrc:/assets/bluecreature-1.svg",
            "qrc:/assets/bluecreature-2.svg",
        ]

        x: -180
        y: 0
    }

    Sprite {
        name: "Johnny"

        costumes: [
            "qrc:/assets/johnny-1.svg",
        ]

        x: -180
        y: 180
    }

    Sprite {
        name: "Martin"

        costumes: [
            "qrc:/assets/martin-1.svg",
            "qrc:/assets/martin-2.svg",
            "qrc:/assets/martin-3.svg",
            "qrc:/assets/martin-4.svg",
            "qrc:/assets/martin-5.svg",
        ]

        x: 180
        y: -180
    }

    Sprite {
        name: "Orange Droid"

        x: 180
        y: 0

        costumes: [
            "qrc:/assets/orangedroid.svg",
        ]
    }

    Sprite {
        name: "Réteg"

        x: 180
        y: 180

        costumes: [
            "qrc:/assets/reteg.svg",
        ]
    }

    Sprite {
        name: "Robot on a Bike"

        x: -180
        y: -180

        costumes: [
            "qrc:/assets/robobike.svg",
        ]
    }
}
