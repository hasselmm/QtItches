import QtItches.Core 1.0
import QtQuick 2.9

Text {
    property ConstantParameter parameter

    color: _qtItches_blockView_.textColor
    font: _qtItches_blockView_.font
    text: parameter ? parameter.string : ""
}
