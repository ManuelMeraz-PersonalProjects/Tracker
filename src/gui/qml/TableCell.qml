import QtQuick 2.12

Rectangle {
    id: root
    property alias text: cellText.text

    implicitWidth: 100
    implicitHeight: 50
    border.color: "black"
    border.width: 2
    Text {
        id: cellText
        text: modelData.city
        font.pointSize: 12
        anchors.fill: parent
        anchors.margins: 10

        color: 'black'
        verticalAlignment: Text.AlignVCenter
    }
}
