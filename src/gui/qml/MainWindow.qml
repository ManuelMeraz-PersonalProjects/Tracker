import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: root
    width: 360
    height: 520
    visible: true
    title: qsTr("Side Panel")

    //! [orientation]
    readonly property bool inPortrait: root.width < root.height
    //! [orientation]

    GuiToolbar {
        id: overlayHeader
        text: "Tracker"
    }

    // Main display under the toolbar
    GuiDisplay {
        id: display
    }

    FlickableScroll {}
}
