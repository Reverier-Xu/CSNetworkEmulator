import QtQuick 2.15

Rectangle {
    id: root
    property bool frameStatus: false
    width: 32
    height: 32
    color: "transparent"

    Rectangle {
        id: content
        anchors.centerIn: parent
        width: 18
        height: 18
        color: frameStatus ? "#009900" : "#808080"
        radius: 4
    }
}
