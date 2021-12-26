import QtQuick 2.15
import "qrc:/components"

Rectangle {
    id: root
    color: "transparent"

    Rectangle {
        anchors.top: senderStation.bottom
        anchors.left: parent.left
        anchors.leftMargin: 48
        anchors.right: parent.right
        anchors.rightMargin: 48
        height: 4
        radius: height / 2
        color: display.themeColor
    }

    Rectangle {
        anchors.bottom: receiverStation.top
        anchors.left: parent.left
        anchors.leftMargin: 48
        anchors.right: parent.right
        anchors.rightMargin: 48
        height: 4
        radius: height / 2
        color: display.themeColor
    }

    Rectangle {
        id: senderStation
        color: "transparent"
        anchors.top: parent.top
        height: root.height / 4
        anchors.left: parent.left
        anchors.right: parent.right

        TextLabel {
            id: senderTitle
            anchors.left: parent.left
            anchors.leftMargin: 48
            anchors.top: parent.top
            anchors.topMargin: 32
            height: 48
            fontSize: 24
            iconSize: 24
            showIcon: true
            icon: "qrc:/assets/send.svg"
            text: "设备 - 数据发送方"
        }
    }

    Rectangle {
        id: receiverStation
        color: "transparent"
        anchors.bottom: parent.bottom
        height: root.height / 4
        anchors.left: parent.left
        anchors.right: parent.right

        TextLabel {
            id: receiverTitle
            anchors.left: parent.left
            anchors.leftMargin: 48
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 32
            height: 48
            fontSize: 24
            iconSize: 24
            showIcon: true
            icon: "qrc:/assets/download.svg"
            text: "设备 - 数据接收方"
        }
    }
}
