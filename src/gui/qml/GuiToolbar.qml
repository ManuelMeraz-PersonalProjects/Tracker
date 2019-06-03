import QtQuick 2.12
import QtQuick.Controls 2.12

ToolBar {
    id: root

    property alias text: label.text

    z: 1
    width: parent.width
    parent: parent.overlay

    Label {
        id: label
        anchors.centerIn: parent
        text: "Toolbar"
    }
}

