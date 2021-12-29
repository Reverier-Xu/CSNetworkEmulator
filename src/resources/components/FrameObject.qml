import QtQuick 2.15

Rectangle {
    id: root
    property bool frameStatus: false
    property color frameColor: frameStatus ? "#009900" : "#808080"
    width: 32
    height: 32
    color: "transparent"

    Rectangle {
        id: content
        anchors.centerIn: parent
        width: 18
        height: 18
        color: frameColor
        radius: 4
    }
}
