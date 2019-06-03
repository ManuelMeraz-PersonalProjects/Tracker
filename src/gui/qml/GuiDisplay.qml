import QtQuick 2.12
import QtQuick.Controls 2.12

Drawer {
    id: root

    y: overlayHeader.height
    width: 200
    height: window.height - overlayHeader.height

    modal: inPortrait
    interactive: inPortrait
    position: inPortrait ? 0 : 1
    visible: !inPortrait

    ListView {
        id: listView
        anchors.fill: parent

        headerPositioning: ListView.OverlayHeader
        header: Pane {
            id: header
            z: 2
            width: parent.width

            contentHeight: logo.height

            Image {
                id: logo
                width: parent.width
                source: "../images/qt-logo.png"
                fillMode: implicitWidth > width ? Image.PreserveAspectFit : Image.Pad
            }

            MenuSeparator {
                parent: header
                width: parent.width
                anchors.verticalCenter: parent.bottom
                visible: !listView.atYBeginning
            }
        }

        footer: ItemDelegate {
            id: footer
            text: qsTr("Footer")
            width: parent.width

            MenuSeparator {
                parent: footer
                width: parent.width
                anchors.verticalCenter: parent.top
            }
        }

        model: ListModel {
            ListElement {
                name: "Bill Smith"
                number: "123"
            }

            ListElement {
                name: "John Brown"
                number: "456"
            }
        }

        delegate: ItemDelegate {
            MouseArea {
                anchors.fill: parent
                onPressed: console.log(name)
            }

            text: name + ": " + number
            width: parent.width
        }

        ScrollIndicator.vertical: ScrollIndicator { }
    }
}
