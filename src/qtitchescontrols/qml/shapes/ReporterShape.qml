import QtQuick 2.9
import QtQuick.Shapes 1.0

BlockShape {
    id: reporterShape

    headerAlignment: Qt.AlignCenter

    topPadding: 2
    leftPadding: height/2
    rightPadding: height/2
    bottomPadding: 2

    PathLine { id: t; x: width - height/2; y: 0.5 }
    PathLine { id: b; x: height/2; y: height - 0.5 }

    PathArc  { id: bl; x: 0.5; y: height/2; radiusX: height/2; radiusY: height/2 }
    PathArc  { id: tr; x: width - 0.5; y: height/2; radiusX: height/2; radiusY: height/2 }

    PathArc  { id: tl; x: height/2; y: 0.5; radiusX: height/2; radiusY: height/2 }
    PathArc  { id: br; x: width - height/2; y: height - 0.5; radiusX: height/2; radiusY: height/2 }

    ShapePath {
        fillColor: reporterShape.fillColor
        strokeColor: reporterShape.strokeColor

        startX: tl.x
        startY: tl.y

        pathElements: [t, tr, br, b, bl, tl]
    }
}
