import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2

import org.example.io 1.0

ApplicationWindow {
    id: root
    title: qsTr("Hello World")
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
            console.log("clicked open")
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

    Food {
        id: taco
        name: "taco"
        fat: 25
    }

    TableView {
        id: view
        anchors.fill: parent
        columnWidthProvider: function (column) { return 300; }
        rowHeightProvider: function (column) { return 60; }

        model: Food {}

        delegate: Rectangle {
            Row {
                spacing: 1
                TableCell { text: taco.key }
                TableCell { text: taco.name }
                TableCell { text: taco.fat }
            }
        }

        ScrollIndicator.vertical: ScrollIndicator {}
        ScrollIndicator.horizontal: ScrollIndicator {}

    }
}