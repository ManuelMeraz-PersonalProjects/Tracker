import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import tracker.food 1.0
import tracker.database 1.0

ApplicationWindow {
    visible: true
    title: qsTr("Tracker")
    background: Rectangle {
        color: "darkGray"
    }

    DatabaseUtils {
        id: database
    }

    TableView {
        id: view
        anchors.fill: parent
        columnWidthProvider: function (column) { return 100; }
        rowHeightProvider: function (column) { return 40; }

        model: database.getData("Food")
        delegate: Rectangle {
            Row {
                spacing: 1
                TableCell { text: modelData.name }
                TableCell { text: modelData.fat }
                TableCell { text: modelData.carbohydrate }
                TableCell { text: modelData.fiber }
                TableCell { text: modelData.protein }
            }
        }

        ScrollIndicator.vertical: ScrollIndicator { width: 10 }
        ScrollIndicator.horizontal: ScrollIndicator { width: 10 }

    }
}
