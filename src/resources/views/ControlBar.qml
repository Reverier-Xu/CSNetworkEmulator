import QtQuick 2.15
import QtGraphicalEffects 1.15
import "qrc:/components"

Rectangle {
    id: root
    color: display.colorStyle ? "#20000000" : "#20FFFFFF"
    Behavior on color {
        ColorAnimation {
            duration: 280
        }
    }
    height: 36

    PushButton {
        id: playButton
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        showIcon: true
        flat: true
        icon: "qrc:/assets/play.svg"
        text: "开始模拟"
        contentColor: display.colorStyle ? "#007000" : "#00AA00"
        onClicked: {
            sender.start()
        }
    }

    PushButton {
        id: clearButton
        anchors.left: playButton.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        showIcon: true
        flat: true
        icon: "qrc:/assets/delete.svg"
        text: "重置状态"
        onClicked: {
            sender.resetAll()
            receiver.clear()
        }
    }

    TextLabel {
        id: sendIntervalTips
        anchors.right: networkDelayTips.left
        anchors.rightMargin: 12
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        showIcon: true
        icon: "qrc:/assets/history.svg"
        text: "发包间隔 :  1700 ms"
    }

    TextLabel {
        id: networkDelayTips
        anchors.right: parent.right
        anchors.rightMargin: 25
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        showIcon: true
        icon: "qrc:/assets/filter.svg"
        text: "网络延迟 :  800 ms"
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: "#30606060"
    }
}
