import QtQuick 2.15
import QtGraphicalEffects 1.15
import "qrc:/components"

Rectangle {
    id: root
    color: display.colorStyle ? "#10000000" : "#10FFFFFF"
    Behavior on color {
        ColorAnimation {
            duration: 280
        }
    }

    TextLabel {
        id: lostLabel
        anchors.top: parent.top
        anchors.topMargin: 12
        anchors.left: parent.left
        height: 32
        showIcon: true
        icon: "qrc:/assets/filter.svg"
        text: "网络丢包率 :  " + (lostSlider.currentValue * 100).toString() + "%"
    }

    SliderBar {
        id: lostSlider
        anchors.right: parent.right
        anchors.left: lostLabel.right
        anchors.leftMargin: 15
        anchors.rightMargin: 25
        anchors.verticalCenter: lostLabel.verticalCenter
        currentValue: 0.1
    }

    TextLabel {
        id: senderLogTips
        anchors.left: parent.left
        anchors.top: lostLabel.bottom
        height: 44
        showIcon: true
        icon: "qrc:/assets/send.svg"
        text: "发送方日志"
    }

    Rectangle {
        id: senderLogWindow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: senderLogTips.bottom
        height: (parent.height - 132) / 2
        color: display.colorStyle?"#20000000":"#10808080"
    }

    TextLabel {
        id: receiverLogTips
        anchors.top: senderLogWindow.bottom
        anchors.left: parent.left
        height: 44
        showIcon: true
        icon: "qrc:/assets/download.svg"
        text: "接收方日志"
    }

    Rectangle {
        id: receiverLogWindow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: receiverLogTips.bottom
        anchors.bottom: parent.bottom
        color: display.colorStyle?"#20000000":"#10808080"
    }

    Rectangle {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.right
        width: 1
        color: "#30606060"
    }
}
