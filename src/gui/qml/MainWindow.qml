import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: window
    width: 360
    height: 520
    visible: true
    title: qsTr("Side Panel")

    //! [orientation]
    readonly property bool inPortrait: window.width < window.height
    //! [orientation]

    GuiToolbar {
        id: overlayHeader
        text: "Tracker"
    }

    // Main display under the toolbar
    GuiDisplay {
        id: display
    }

    Flickable {
        id: flickable
        width: 360

        anchors.fill: parent
        anchors.topMargin: overlayHeader.height
        anchors.leftMargin: !inPortrait ? display.width : undefined

        topMargin: 20
        bottomMargin: 20

        ScrollIndicator.vertical: ScrollIndicator { }
    }


}
