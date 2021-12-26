import QtQuick 2.15

Rectangle {
    id: root
    property int frameStatus: 0 // 0 is undefined, 1 is sent, 2 is droped
    property alias frameData: innerText.text
    width: 64
    height: 32
    color: frameStatus == 0 ? "#20808080" : (frameStatus == 1 ? display.themeColor : display.alertColor)
    border.width: 2
    radius: 2
    border.color: "#10000000"

    Text {
        id: innerText
        anchors.centerIn: parent
        font.pixelSize: 16
        color: frameStatus == 0 ? display.contentColor : "white"
    }
}
