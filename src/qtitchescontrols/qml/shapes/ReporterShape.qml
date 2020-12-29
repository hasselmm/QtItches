import QtQuick 2.15
import QtQuick.Shapes 1.15

BlockShape {
    id: reporterShape

    headerAlignment: Qt.AlignCenter

    topPadding: 2
    leftPadding: height/2
    rightPadding: height/2
    bottomPadding: 2

    layer {
        enabled: true
        samples: 4
    }

    readonly property real __r: height/2
    readonly property real __c: __r * 0.551915024494 // http://spencermortensen.com/articles/bezier-circle/

    PathLine { id: b; x: __r; y: height - 0.5 }
    PathLine { id: t; x: width - __r; y: 0.5 }

    PathCubic {
        id: bl

        control1X: b.x - __c; control2X: x; x: 1.0
        control1Y: b.y; control2Y: y + __c; y: __r
    }

    PathCubic {
        id: tl

        control1X: bl.x; control2X: x - __c; x: b.x
        control1Y: bl.y - __c; control2Y: y; y: t.y
    }


    PathCubic {
        id: tr

        control1X: t.x + __c; control2X: x; x: width - 1.0
        control1Y: t.y; control2Y: y - __c; y: __r
    }

    PathCubic {
        id: br

        control1X: tr.x; control2X: x + __c; x: t.x
        control1Y: tr.y + __c; control2Y: y; y: b.y
    }

    ShapePath {
        fillColor: reporterShape.fillColor
        strokeColor: reporterShape.strokeColor

        startX: tl.x
        startY: tl.y

        pathElements: [t, tr, br, b, bl, tl]
    }
}
