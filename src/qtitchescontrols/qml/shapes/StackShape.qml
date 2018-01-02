import QtQuick 2.9
import QtQuick.Shapes 1.0

BlockShape {
    id: stackShape

    property real bayHeight

    topPadding: hasTopConnector ? 5 : 15

    // top left corner
    PathLine { id: tl1; x: 0; y: 2 }
    PathLine { id: tl2; x: 2; y: 0 }
    // top connector
    PathLine { id: tc1; x: 12.5; y: 0.5 }
    PathLine { id: tc2; x: 15.5; y: 3.5 }
    PathLine { id: tc3; x: 24.5; y: 3.5 }
    PathLine { id: tc4; x: 27.5; y: 0.5 }
    // top right corner
    PathLine { id: tr1; x: width - 2.5; y: 0.5 }
    PathLine { id: tr2; x: width - 0.5; y: 2.5 }

    // bottom left corner
    PathLine { id: bl1; x: 2.5; y: height - 0.5 }
    PathLine { id: bl2; x: 0.5; y: height - 2.5 }
    // bottom connector
    PathLine { id: bc1; x: 27.5; y: height - 0.5 }
    PathLine { id: bc2; x: 24.5; y: height + 2.5 }
    PathLine { id: bc3; x: 15.5; y: height + 2.5 }
    PathLine { id: bc4; x: 12.5; y: height - 0.5 }
    // bottom right corner
    PathLine { id: br1; x: width - 0.5; y: height - 2.5 }
    PathLine { id: br2; x: width - 2.5; y: height - 0.5 }

    // top hat
    PathLine { id: th1; x: 0.5; y: 10.5 }
    PathArc  { id: th2; x: 80.5; y: 10.5; radiusX: 40; radiusY: 10/*; direction: PathArc.Counterclockwise*/ }
    PathLine { id: th3; x: width - 2.5; y: 10.5 }
    PathLine { id: th4; x: width - 0.5; y: 12.5 }

    Component { id: pathLine; PathLine {} }

    ShapePath {
        id: shapePath

        fillColor: stackShape.fillColor
        strokeColor: stackShape.strokeColor

        startX: (hasTopConnector ? tr2 : th4).x
        startY: (hasTopConnector ? tr2 : th4).y

        pathElements: {
            var path = [];

            (scriptViews || []).forEach(function(view) {
                var y0 = view.y + view.labelPadding + 0.5;
                var y1 = view.y + view.height - 0.5;

                path.push(pathLine.createObject(shapePath, {x: startX, y: y0 - 2}),
                          pathLine.createObject(shapePath, {x: startX - 2, y: y0}),
                          pathLine.createObject(shapePath, {x: 42.5, y: y0}),
                          pathLine.createObject(shapePath, {x: 39.5, y: y0 + 3}),
                          pathLine.createObject(shapePath, {x: 30.5, y: y0 + 3}),
                          pathLine.createObject(shapePath, {x: 27.5, y: y0}),
                          pathLine.createObject(shapePath, {x: 16.5, y: y0}),
                          pathLine.createObject(shapePath, {x: 15.5, y: y0 + 2}),
                          pathLine.createObject(shapePath, {x: 15.5, y: y1 - 2}),
                          pathLine.createObject(shapePath, {x: 16.5, y: y1}),
                          pathLine.createObject(shapePath, {x: startX - 2, y: y1}),
                          pathLine.createObject(shapePath, {x: startX, y: y1 + 2}));

/*
*/
            });

            path.push(br1, br2);

            if (hasBottomConnector)
                path.push(bc1, bc2, bc3, bc4);

            path.push(bl1, bl2);

            if (hasTopConnector) {
                path.push(tl1, tl2);
                path.push(tc1, tc2, tc3, tc4);
                path.push(tr1, tr2);
            } else {
                path.push(th1, th2, th3, th4);
            }

            return path;
        }
    }
 }
