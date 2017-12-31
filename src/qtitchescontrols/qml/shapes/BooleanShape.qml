import QtQuick 2.9
import QtQuick.Shapes 1.0

BlockShape {
    id: booleanShape

    headerAlignment: Qt.AlignCenter

    topPadding: 2
    leftPadding: height/2
    rightPadding: height/2
    bottomPadding: 2

    PathLine { id: tl; x: height/2; y: 0.5 }
    PathLine { id: bl; x: height/2; y: height - 0.5 }

    PathLine { id: cl; x: 0.5; y: height/2 }
    PathLine { id: cr; x: width - 0.5; y: height/2 }

    PathLine { id: tr; x: width - height/2; y: 0.5 }
    PathLine { id: br; x: width - height/2; y: height - 0.5 }

    ShapePath {
        fillColor: booleanShape.fillColor
        strokeColor: booleanShape.strokeColor

        startX: cl.x
        startY: cl.y

        pathElements: [bl, br, cr, tr, tl, cl]
    }
}
