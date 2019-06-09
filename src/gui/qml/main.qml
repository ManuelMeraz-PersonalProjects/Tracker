import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

ImageViewerWindow {

    id: root
    width: 640
    height: 480
    visible: true

    Action {
        id: save
        text: qsTr("&Save")
        shortcut: StandardKey.Save
        onTriggered: {
            console.log("click saved")
        }
    }

    Action {
        id: open
        text: qsTr("&Open")
        shortcut: StandardKey.Open
        onTriggered: {
            utils.foodData[0].name = "not tacos"
        }
    }

    Action {
        id: exit
        text: qsTr("&Exit")
        onTriggered: Qt.quit();
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem { action: open }
            MenuItem { action: save }
            MenuSeparator {}
            MenuItem { action: exit }
        }
    }
}
