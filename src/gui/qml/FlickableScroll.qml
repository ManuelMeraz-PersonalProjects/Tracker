import QtQuick 2.12
import QtQuick.Controls 2.12

Flickable {
    id: root
    width: parent.width

    anchors.fill: parent
    anchors.topMargin: overlayHeader.height
    anchors.leftMargin: !inPortrait ? display.width : undefined

    topMargin: 20
    bottomMargin: 20

    ScrollIndicator.vertical: ScrollIndicator { }
}
