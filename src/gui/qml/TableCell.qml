import QtQuick 2.12

Rectangle {
    id: root
    property alias text: cellText.text

    implicitWidth: 100
    implicitHeight: 40

    Text {
        id: cellText
        text: modelData.city
        font.pointSize: 12
        anchors.fill: parent
        anchors.margins: 5

        color: 'black'
        verticalAlignment: Text.AlignVCenter
    }
}
